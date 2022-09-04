#include "stdafx.h"
#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}