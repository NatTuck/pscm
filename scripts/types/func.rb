
require './types/0v.rb'

class FuncV < VV
  def initialize
    super
    @psv_attrs << "params"
    @psv_attrs << "body"
    @psv_attrs << "env"
  end

  def make_body
  end

  def show_body
    <<-END
    ss = pscm_sprintf("(lambda %s %s)", pscm_show(vv->params), pscm_show(vv->body));
    END
  end

  def clean_body
  end

  def equal_body
    %Q{fatal_error("func doesn't do equality");}
  end
end
