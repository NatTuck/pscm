#!/usr/bin/env ruby

fs = []
fs << ["+", "int_add", ["int", "int"], "int"]
fs << ["-", "int_sub", ["int", "int"], "int"]
fs << ["*", "int_mul", ["int", "int"], "int"]
fs << ["/", "int_div", ["int", "int"], "int"]
fs << ["=", "int_eq",  ["int", "int"], "bool"]  

def lookup_type(t)
  case t
  when "int"
    "int64_t"
  when "bool"
    "int8_t"
  else
    t
  end
end

hh = File.open("../include/gen/prelude.h", "w")
cc = File.open("../src/gen/prelude.c", "w")

hh.puts <<-END
#ifndef PSCM_GEN_PRELUDE_H
#define PSCM_GEN_PRELUDE_H

//#ifndef PSCM_STDLIB_H
//#error "Don't include gen/prelude.h directly"
//#endif

#include "types.h"

END

cc.puts <<-END
#include "types.h"
#include "lists.h"
#include "stdlib.h"
#include "numbers.h"
END

fs.each do |fun|
  sn, cn, args, rt = fun

  hh.puts <<-"END"
ps_v* #{cn}_wrapper(ps_v* xs);
  END

  cc.puts <<-"END"
ps_v*
#{cn}_wrapper(ps_v* xs)
{
  END

  args1 = []

  args.each_with_index do |aa, ii|
    args1 << "x#{ii}"

    cc.puts <<-"END"
      #{lookup_type(aa)} x#{ii} = unwrap_ps_#{aa}(list_ref_c(xs, #{ii}));
    END
  end

  cc.puts <<-"END"
      #{lookup_type(rt)} yy = #{cn}(#{args1.join(', ')});
      return make_ps_#{rt}(yy);
}
  END
end

cc.puts <<-END
ps_v*
initial_env()
{
    ps_v* env = make_ps_nil();
    ps_v* nam = 0;
    ps_v* fun = 0;
END

fs.each do |fun|
  sn, cn, _, _ = fun

  cc.puts <<-"END"
    nam = make_ps_symbol("#{sn}");
    fun = make_ps_native(#{cn}_wrapper);
    env = plist_put(env, nam, fun);
  END
end

cc.puts <<-END
   return env;
}
END

hh.puts <<-END
ps_v* initial_env();

#endif
END

cc.close
hh.close
