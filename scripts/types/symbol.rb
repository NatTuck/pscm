
require './types/0v.rb'

class SymbolV < VV
  def initialize
    super
    @attrs << "char* text"
  end
end
