
require './types/0v.rb'

class FloatV < VV
  def initialize
    super
    @attrs << "double num"
  end

  def equal_body
    %Q{fatal_error("float doesn't do equality");}
  end
end
