
require './types/0v.rb'

class NilV < VV
  def show_body
    %Q{ss = pscm_strdup("nil");}
  end

  def clean_body
    ""
  end
end
