//
// C++ Implementation: wnumberrate
//
// Description:
//
//
// Author: Tue Haste Andersen <haste@diku.dk>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "widget/wnumberrate.h"

#include "control/controlobject.h"
#include "control/controlproxy.h"
#include "util/math.h"

namespace {

inline QChar sign(double number) {
    if (number > 0) {
        return '+';
    }
    if (number < 0) {
        return '-';
    }
    return ' ';
}
}

WNumberRate::WNumberRate(const char * group, QWidget * parent)
        : WNumber(parent) {
    m_pRateRangeControl = new ControlProxy(group, "rateRange", this);
    m_pRateRangeControl->connectValueChanged(SLOT(setValue(double)));
    m_pRateDirControl = new ControlProxy(group, "rate_dir", this);
    m_pRateDirControl->connectValueChanged(SLOT(setValue(double)));
    m_pRateControl = new ControlProxy(group, "rate", this);
    m_pRateControl->connectValueChanged(SLOT(setValue(double)));
    // Initialize the widget.
    setValue(0);
}

void WNumberRate::setValue(double dValue) {
    const double rateRange = m_pRateRangeControl->get();
    const double rateDir = m_pRateDirControl->get();
    const double digitFactor = pow(10, m_iNoDigits);
    // Calculate percentage rounded to the number of digits specified by iNoDigits
    const double percentage = round(dValue * rateRange * rateDir * 100.0 * digitFactor) / digitFactor;

    setText(m_skinText + sign(percentage) + QString::number(fabs(percentage), 'f', m_iNoDigits));
}
