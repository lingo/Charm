ActivityReportTemplater::loadTemplate(const QString & templateName)
{
    return engine->loadByName(templateName);
}

ActivityReportTemplater::populateContext(
    const ActivityReportConfigurationDialog::Properties &properties)
{

    const Grantlee::Template & template = loadTemplate();

    QVariantHash templateData;

    templateData.insert("caption",      tr("Activity Report"));
    templateData.insert("userName",     CONFIGURATION.user.name());
    templateData.insert("startDate",    properties.start.toString(Qt::TextDate));
    templateData.insert("endDate",      properties.start.toString(Qt::TextDate));
    templateData.insert("timeSpan",     timeSpanTypeName);
    templateData.insert("totalsText",   tr("Total: %1").arg(hoursAndMinutes(totalSeconds)));

    if (!properties.rootTasks.isEmpty()) {
        QString rootTaskText = tr("Activity under tasks:"));

        Q_FOREACH (TaskId taskId, properties.rootTasks) {
            const Task &task = DATAMODEL->getTask(taskId);
            rootTaskText.append(QStringLiteral(" ( %1 ),").arg(DATAMODEL->fullTaskName(task)));
        }

        rootTaskText = rootTaskText.mid(0, rootTaskText.length() - 1);
        templateData.insert("rootTaskText", rootTaskText);
    }


    QVariantList rootTasks;




    mapping.insert("mydouble", 6.5); // Can insert doubles
    mapping.insert("mybool", false); // Can insert bools
    QVariantList mylist;
    mylist << "Ingrid" << 3;
    mapping.insert("mylist", mylist); // Can insert QVariantList
    QVariantHash myhash;
    myhash.insert("James", "Artist");
    myhash.insert("Kiera", "Dreamer");
    mapping.insert("myhash", myhash); // Can insert QVariantHash
    QObject *obj;
    QVariant objVar = QVariant::fromValue(obj);
    mapping.insert("myobject", objVar); // Can insert QObject*

    Grantlee::Context c(mapping);
    return t->render(&c);
}