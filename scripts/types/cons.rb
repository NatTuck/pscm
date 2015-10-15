
require './types/0v.rb'

class ConsV < VV
  def initialize
    super
    @psv_attrs << "car"
    @psv_attrs << "cdr"
  end

  def show_body
    <<-END
      char* aa = pscm_show(vv->car);
      char* bb = pscm_show(vv->cdr);
      ss = pscm_sprintf("(cons %s %s)", aa, bb);
      pscm_free(bb);
      pscm_free(aa);
    END
  end

  def clean_body
    ""
  end
end
