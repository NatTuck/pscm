
require './types/0v.rb'

class FloatV < VV
  def initialize
    super
    @attrs << "double num"
  end
end
