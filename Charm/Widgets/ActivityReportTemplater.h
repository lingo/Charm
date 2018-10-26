#ifndef ACTIVITYREPORTTEMPLATER_H
#define ACTIVITYREPORTTEMPLATER_H

#include "../grantlee/templates/lib/template.h"

class ActivityReportTemplater
{
public:
    ActivityReportTemplater(const QString & templateName);

private:
    const Grantlee::Template & loadTemplate(const QString & templateName);
    const Grantlee::Context &  populateContext(const ActivityReportConfigurationDialog::Properties &properties);
};

#endif