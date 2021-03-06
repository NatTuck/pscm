
require './types/0v.rb'

class IntV < VV
  def initialize
    super
    @attrs << "int64_t num"
  end

  def make_body
    %Q{vv->num = num;}
  end

  def show_body
    %Q{ss = pscm_sprintf("%d", vv->num);}
  end

  def equal_body
    "return xx_->num == yy_->num;"
  end
end
