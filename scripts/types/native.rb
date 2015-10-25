
require './types/0v.rb'

class NativeV < VV
  def initialize
    super
    @attrs << "native_func code"
  end

  def make_body
    "vv->code = code;"
  end

  def show_body
    %Q{ss = pscm_strdup("[native]");}
  end

  def clean_body
  end

  def equal_body
    %Q{fatal_error("native doesn't do equality");}
  end
end
