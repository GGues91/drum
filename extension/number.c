#include "number.h"

TO(number)
{
  totoken(ttn_number | ttn_property_type);
  tt.number.n = stoi(to->p);
}
