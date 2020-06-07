#include "newline.h"
#include "toxy.h"

TO(newline)
{
  totoken(ttn_end_of_line);
  tox = toxy_start_x; toy += 1;
}
