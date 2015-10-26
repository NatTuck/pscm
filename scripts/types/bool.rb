
require './types/0v.rb'

class BoolV < VV
  def initialize
    super
    @attrs << "int8_t val"
  end

  def make_body
    %Q{vv->val = val;}
  end

  def show_body
    <<-END
    if (vv->val) {
        return pscm_strdup("true");
    }
    else {
        return pscm_strdup("false");
    }
    END
  end

  def equal_body
    "return xx_->val == yy_->val;"
  end
end
