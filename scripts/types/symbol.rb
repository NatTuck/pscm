
require './types/0v.rb'

class SymbolV < VV
  def initialize
    super
    @attrs << "char* text"
  end

  def make_body
    "vv->text = pscm_strdup(text);"
  end
  
  def clean_body
    "pscm_free(vv->text);"
  end

  def show_body
    "ss = pscm_strdup(vv->text);"
  end

  def equal_body
    <<-"END"
    int diff = strcmp(xx_->text, yy_->text);
    if (diff == 0) {
        return 1;
    }
    END
  end
end
