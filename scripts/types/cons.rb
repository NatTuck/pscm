
require './types/0v.rb'

class ConsV < VV
  def initialize
    super
    @psv_attrs << "car"
    @psv_attrs << "cdr"
  end
end
