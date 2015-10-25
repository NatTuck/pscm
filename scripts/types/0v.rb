
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
    code = <<-"END"
    #{type_type_name}.name    = "#{type_name}";
    #{type_type_name}.clone   = clone_#{type_name};
    #{type_type_name}.show    = show_#{type_name};
    #{type_type_name}.equal   = equal_#{type_name};
    #{type_type_name}.cleanup = 0;
    END
   
    if has_cleanup?
      code += "#{type_type_name}.cleanup = cleanup_#{type_name};\n"
    end

    code
  end

  def protos
    xs = []
    xs << is_proto
    xs << make_proto
    xs << clone_proto
    xs << show_proto
    xs << equal_proto
    xs << clean_proto  if has_cleanup?
    xs << unwrap_proto if has_unwrap?
    xs << ''
    xs.join("\n")
  end

  def impls
    xs = []
    xs << is_impl
    xs << make_impl
    xs << clone_impl
    xs << show_impl
    xs << equal_impl
    xs << clean_impl  if has_cleanup?
    xs << unwrap_impl if has_unwrap?
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

  def is_proto
    "int is_#{type_name}(ps_v* vv);"
  end

  def is_impl
    <<-"END"
int
is_#{type_name}(ps_v* vv)
{
    return vv->type == &#{type_type_name};
}
    END
  end

  def make_proto
    "ps_v* make_#{type_name}(#{attrs.join(", ")});"
  end

  def make_impl
    code = <<-END
ps_v*
make_#{type_name}(#{attrs.join(", ")})
{
    //fprintf(stderr, "make #{type_name}\\n");

#ifdef REFCOUNT
    #{type_name}* vv = calloc(1, sizeof(#{type_name}));
    vv->refs = 1;
#else
    #{type_name}* vv = GC_malloc(sizeof(#{type_name}));
#endif
    vv->type = &#{type_type_name};
    END

    @psv_attrs.each do |vv|
      code << "    vv->#{vv} = #{vv};\n"
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

  def has_cleanup?
    false
  end

  def clean_proto
    "void cleanup_#{type_name}(ps_v* vv);"
  end

  def clean_impl
    <<-END
void
cleanup_#{type_name}(ps_v* xx)
{
    #{type_name}* vv = (#{type_name}*) xx;
    #{clean_body}
}
    END
  end

  def clean_body
    %Q{fatal_error("that's a leak, #{type_name}");}
  end

  def clone_proto
    "ps_v* clone_#{type_name}(ps_v*);"
  end

  def clone_impl
    <<-END
ps_v*
clone_#{type_name}(ps_v* vv)
{
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

  def has_unwrap?
    @attrs.count == 1
  end
  
  def unwrap_type
    tt, _ = @attrs[0].split(/\s+/)
    tt
  end

  def unwrap_attr
    _, aa = @attrs[0].split(/\s+/)
    aa
  end


  def unwrap_proto
    %Q{#{unwrap_type} unwrap_#{type_name}(ps_v* vv);}
  end

  def unwrap_impl
    <<-"END"
#{unwrap_type}
unwrap_#{type_name}(ps_v* vv)
{
    hard_assert(vv->type == &#{type_type_name}, "Not a #{type_name}");
    #{type_name}* vv_ = (#{type_name}*)vv;
    #{unwrap_type} yy = vv_->#{unwrap_attr};
    #{unwrap_body}
    return yy;
}
    END
  end

  def unwrap_body
    ""
  end

  def equal_proto
    "int equal_#{type_name}(ps_v* xx, ps_v* yy);"
  end

  def equal_impl
    <<-"END"
int
equal_#{type_name}(ps_v* xx, ps_v* yy)
{
    #{type_name}* xx_ = (#{type_name}*) xx;
    #{type_name}* yy_ = (#{type_name}*) yy;
    #{equal_body}
    return xx_ == yy_;
}
    END
  end

  def equal_body
    ""
  end
end

