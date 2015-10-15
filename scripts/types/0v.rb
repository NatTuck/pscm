
class VV
  def initialize
    @attrs     = []
    @psv_attrs = []
  end

  def type_type_name
    "#{type_name.upcase}_TYPE"
  end

  def type_decl
    "extern ps_type #{type_type_name};"
  end

  def type_defn
    "ps_type #{type_type_name};"
  end

  def type_init
    <<-"END"
    #{type_type_name}.name    = "#{type_name}";
    #{type_type_name}.cleanup = cleanup_#{type_name};
    #{type_type_name}.clone   = clone_#{type_name};
    #{type_type_name}.show    = show_#{type_name};
    END
  end

  def protos
    xs = []
    xs << make_proto
    xs << clean_proto
    xs << clone_proto
    xs << show_proto
    xs << ''
    xs.join("\n")
  end

  def impls
    xs = []
    xs << make_impl
    xs << clean_impl
    xs << clone_impl
    xs << show_impl
    xs << ''
    xs.join("\n")
  end

  def struct
    xs = []
    xs << "typedef struct #{type_name} {"
    xs << "    int64_t  refs;"
    xs << "    ps_type* type;"

    @attrs.each do |ff|
      xs << "    #{ff};";
    end
    @psv_attrs.each do |pv|
      xs << "    ps_v* #{pv};";
    end
    xs << "} #{type_name};"
    xs << ""
    xs.join("\n")
  end

  def attrs
    as = @attrs.clone
    @psv_attrs.each do |vv|
      as << "ps_v* #{vv}"
    end
    as
  end

  def make_proto
    "ps_v* make_#{type_name}(#{attrs.join(", ")});"
  end

  def make_impl
    code = <<-END
ps_v*
make_#{type_name}(#{attrs.join(", ")})
{
    fprintf(stderr, "make #{type_name}\\n");

#ifdef REFCOUNT
    #{type_name}* vv = calloc(1, sizeof(#{type_name}));
    vv->refs = 1;
#else
    #{type_name}* vv = GC_malloc(sizeof(#{type_name}));
#endif
    vv->type = &#{type_type_name};
    END

    @psv_attrs.each do |vv|
      raise Exception.new("clone here is a problem")
      code << "    vv->#{vv} = pscm_clone(#{vv});\n"
    end

    code << <<-END
#{make_body}
    return (ps_v*) vv;
}
    END

    code
  end

  def make_body
    ""
  end

  def clean_proto
    "void cleanup_#{type_name}(ps_v* vv);"
  end

  def clean_impl
    code = <<-END
void
cleanup_#{type_name}(ps_v* xx)
{
    fprintf(stderr, "cleanup #{type_name}\\n");

#ifdef REFCOUNT
    #{type_name}* vv = (#{type_name}*) xx;
    #{clean_body}
    END

    @psv_attrs.each do |pv|
      code += %Q{    pscm_release(vv->#{pv});\n}
    end

    code += <<-END
    free(vv);
#endif
}
    END
    code
  end

  def clean_body
    %Q{hard_assert(0, "that's a leak, #{type_name}");}
  end

  def clone_proto
    "ps_v* clone_#{type_name}(ps_v*);"
  end

  def clone_impl
    <<-END
ps_v*
clone_#{type_name}(ps_v* vv)
{
#ifdef REFCOUNT
    vv->refs += 1;
#endif
    #{clone_body}
    return vv;
}
    END
  end

  def clone_body
    ""
  end

  def show_proto
    "char* show_#{type_name}(ps_v*);"
  end

  def show_impl
    <<-END
char*
show_#{type_name}(ps_v* xx)
{
    #{type_name}* vv = (#{type_name}*) xx;
    char* ss = 0;
    #{show_body}
    hard_assert(ss != 0 && vv != 0, "don't know how to print this");
    return ss;
}
    END
  end

  def show_body
    ""
  end

  def type_name
    base = self.class.to_s.downcase.sub(/v$/, '')
    "ps_#{base}"
  end
end

