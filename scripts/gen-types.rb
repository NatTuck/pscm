#!/usr/bin/env ruby

files = `ls types/*.rb`.split("\n")

hh = File.open("../include/gen/types.h", "w")

hh.puts <<-END
#ifndef PSCM_GEN_TYPES_H
#define PSCM_GEN_TYPES_H

#ifndef PSCM_TYPES_H
#error "Don't include gen/types.h directly"
#endif

#include <stdint.h>
END

cc = File.open("../src/gen/types.c", "w")

cc.puts <<-END
#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>

#include "errors.h"
#include "io.h"
#include "types.h"
#include "mem.h"
END

types = files.map do |pp|
  type = pp.match(/^types\/0?(.*)\.rb$/)[1]
  require "./#{pp}"
  eval "#{type.capitalize}V.new"
end

types.each do |ty|
  hh.puts(ty.type_decl)
  cc.puts(ty.type_defn)
end

hh.puts "void pscm_init_types();"

types.each do |ty|
  hh.puts(ty.struct)
  hh.puts(ty.protos)

  cc.puts(ty.impls)
end

cc.puts <<-END
void
pscm_init_types()
{
END

types.each do |ty|
  cc.puts ty.type_init
end

cc.puts "}"

cc.close()

hh.puts <<-END
#endif
END

hh.close()
