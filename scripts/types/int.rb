
require './types/0v.rb'

class IntV < VV
  def initialize
    super
    @attrs << "int64_t num"
  end
end
