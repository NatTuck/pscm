#!/usr/bin/env ruby

fs = []
fs << ["+", "int_add", ["int", "int"], "int"]
fs << ["-", "int_sub", ["int", "int"], "int"]
fs << ["*", "int_mul", ["int", "int"], "int"]
fs << ["/", "int_div", ["int", "int"], "int"]


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
      #{aa} x#{ii} = unwrap_ps_#{aa}(list_ref_c(xs, #{ii}));
    END
  end

  cc.puts <<-"END"
      #{rt} yy = #{cn}(#{args1.join(', ')});
      return make_ps_#{rt}(yy);
}
  END
end

cc.puts <<-END
ps_v*
initial_env()
{
    ps_v* env = make_ps_nil();
    ps_v* fun = 0;
END

fs.each do |fun|
  _, cn, _, _ = fun

  cc.puts <<-"END"
    fun = make_ps_native(#{cn}_wrapper);
    env = make_ps_cons(fun, env);
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
