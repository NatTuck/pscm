
require './types/0v.rb'

class FuncV < VV
  def initialize
    super
    @psv_attrs << "params"
    @psv_attrs << "code"
  end

  def make_body
  end

  def show_body
  end

  def clean_body
  end

  def equal_body
    %Q{fatal_error("func doesn't do equality");}
  end
end
