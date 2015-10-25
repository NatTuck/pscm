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
END

cc.puts <<-END
#include "gen/prelude.h"

END

fs.each do |fun|
  sn, cn, args, rt = fun

  hh.puts <<-"END"
sp_v* #{cn}_wrapper(sp_v* xs);
  END

  cc.puts <<-"END"
sp_v*
#{cn}_wrapper(sp_v* xs)
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

hh.puts <<-END
#endif
END

cc.close
hh.close
