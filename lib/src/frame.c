#include "frame.h"

void Free_Frame(frame_ptr frame)
{
  _ffree(frame->buffer);
  _ffree(frame);
}