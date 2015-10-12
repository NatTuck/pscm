
require './types/0v.rb'

class StringV < VV
  def initialize
    super
    @attrs << "char* text"
  end

  def make_body
    "vv->text = pscm_strdup(text);"
  end

  def clean_body
    "pscm_free(vv->text);"
  end
end
