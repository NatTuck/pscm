
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
    END
  end

  def protos
    xs = []
    xs << make_proto
    xs << clean_proto
    xs << clone_proto
    xs << ''
    xs.join("\n")
  end

  def impls
    xs = []
    xs << make_impl
    xs << clean_impl
    xs << clone_impl
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
#ifdef REFCOUNT
    #{type_name}* vv = calloc(1, sizeof(#{type_name}));
    vv->refs = 1;
#else
    #{type_name}* vv = GC_malloc(sizeof(#{type_name}));
#endif
    END

    @psv_attrs.each do |vv|
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
    <<-END
void
cleanup_#{type_name}(ps_v* xx)
{
#ifdef REFCOUNT
    #{type_name}* vv = (#{type_name}*) xx;
    #{clean_body}
    free(vv);
#endif
}
    END
  end

  def clean_body
    ""
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

  def type_name
    base = self.class.to_s.downcase.sub(/v$/, '')
    "ps_#{base}"
  end
end
