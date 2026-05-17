#include "attendance.h"
#include "ui_attendance.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDate>

attendance::attendance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::attendance)
{
    ui->setupUi(this);
    initStudentData();

    QStringList groups = groupStudents.keys();
    ui->groupComboBox->addItems(groups);

    connect(ui->groupComboBox, &QComboBox::currentTextChanged,
            this, &attendance::onGroupChanged);
    connect(ui->exportButton, &QPushButton::clicked,
            this, &attendance::onExportClicked);

    if (!groups.isEmpty())
        onGroupChanged(groups.first());
}

attendance::~attendance()
{
    delete ui;
}

void attendance::onGroupChanged(const QString &group)
{
    // Clear existing checkboxes
    qDeleteAll(checkBoxes);
    checkBoxes.clear();

    const QVector<Student> &students = groupStudents[group];
    for (const Student &s : students) {
        auto *cb = new QCheckBox(s.id + "  " + s.name);
        cb->setChecked(true);
        ui->studentsLayout->addWidget(cb);
        checkBoxes.append(cb);
    }

    // Add spacer at the bottom
    ui->studentsLayout->addStretch();
}

void attendance::onExportClicked()
{
    QString group = ui->groupComboBox->currentText();
    if (group.isEmpty()) return;

    QString defaultName = "Attendance_" + group + "_" + QDate::currentDate().toString("yyyy-MM-dd") + ".txt";
    QString filePath = QFileDialog::getSaveFileName(this, "Export Attendance", defaultName, "Text Files (*.txt)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "Attendance Report\n";
    out << "Group: " << group << "\n";
    out << "Date: " << QDate::currentDate().toString("yyyy-MM-dd") << "\n";
    out << "========================================\n\n";

    const QVector<Student> &students = groupStudents[group];
    for (int i = 0; i < students.size(); ++i) {
        QString status = checkBoxes[i]->isChecked() ? "Present" : "Absent";
        out << students[i].id << "  " << students[i].name << "  —  " << status << "\n";
    }

    int present = 0;
    for (auto *cb : checkBoxes)
        if (cb->isChecked()) ++present;

    out << "\n========================================\n";
    out << "Total: " << students.size() << "  |  Present: " << present << "  |  Absent: " << (students.size() - present) << "\n";

    file.close();
    QMessageBox::information(this, "Exported", "Attendance saved to:\n" + filePath);
}

void attendance::initStudentData()
{
    // CIE-25-01
    groupStudents["CIE-25-01"] = {
        {"U2510001", "RAJABBOYEV FUZAYLBEK"},
        {"U2510002", "SHOMURODOV JALOLIDDIN"},
        {"U2510003", "TO'RAYEV ARSLONBEK"},
        {"U2510004", "VALIYEV DALER"},
        {"U2510005", "AKBARALIYEV AVAZBEK"},
        {"U2510006", "KO'CHAROV SANJAR"},
        {"U2510007", "KAMOLOV KARIM"},
        {"U2510008", "MATRIZAYEV SHOXRUH"},
        {"U2510009", "JUMABOYEV NODIRBEK"},
        {"U2510010", "ABDULLAYEV AHMADXON"},
        {"U2510011", "USMONJONOV DAVRONBEK"},
        {"U2510012", "TURSUNOV MUNIS"},
        {"U2510013", "AKBARXONOVA ASLIYAXON"},
        {"U2510014", "DOBRININ VIKTOR"},
        {"U2510015", "OBIDOV ABDUAZIM"},
        {"U2510016", "ASHUROV JAHONGIR"},
        {"U2510017", "VERSHKOV YAN"},
        {"U2510018", "KIM FYODOR"},
        {"U2510019", "NEMATULLAYEVA SHAHINA"},
        {"U2510020", "ABDURAXMONOV SARVAR"},
        {"U2510021", "OKILOV DONIYORJON"},
        {"U2510022", "TURDIYEV MUHAMMAD ALI"},
        {"U2510023", "LI VIKTOR"},
        {"U2510024", "SIM ANDREY"},
        {"U2510025", "BAZAROV AKBAR"},
    };

    // CIE-25-02
    groupStudents["CIE-25-02"] = {
        {"U2510026", "MIRMAXMUDOVA DURDONA"},
        {"U2510027", "XEGAY OLEG"},
        {"U2510028", "NOSIRBEKOV UMARBEK"},
        {"U2510029", "ZARIMBETOV DAULETNAZAR"},
        {"U2510030", "AMRIYEV JAXONGIR"},
        {"U2510031", "RAVSHANOV MEXROJBEK"},
        {"U2510032", "IBRAGIMOVA AZIZAXON"},
        {"U2510033", "BAHODIROVA SUG'DIYONA"},
        {"U2510034", "TOSHPULATOV ASADBEK"},
        {"U2510035", "XON VIKTORIYA"},
        {"U2510036", "USMONOV SAIDALI"},
        {"U2510037", "KINDER VLADIMIR"},
        {"U2510038", "KARIMOV SARDORBEK"},
        {"U2510039", "ABDURAHIMOV MUHAMMADYUSUF"},
        {"U2510040", "BAXTIYOROVA PARIZOD"},
        {"U2510041", "BAXTIYOROV DIYORJON"},
        {"U2510042", "SIRAZETDINOV ASXAR"},
        {"U2510043", "FOZILJONOV ODILJON"},
        {"U2510044", "TAYIROVA XULKAR"},
        {"U2510045", "ABDULLAYEV ABUBAKR"},
        {"U2510046", "SALIMOV JAVOHIR"},
        {"U2510047", "BABARAXIMOVA SAFINA"},
        {"U2510048", "KALANDAROV SHAXZOD"},
        {"U2510049", "MUXAMEDJANOV ARTYOM"},
        {"U2510050", "MIRFOZILOV MIRABBOS"},
    };

    // CIE-25-03
    groupStudents["CIE-25-03"] = {
        {"U2510051", "MASHANLO AKBARALI"},
        {"U2510052", "UDAYEVA MALIKA"},
        {"U2510053", "A'ZAMOV SAIDKAMOLXON"},
        {"U2510054", "XOLBOYEVA RUSHANA"},
        {"U2510055", "XUDOYAROV XONDAMIR"},
        {"U2510056", "ABDUKARIMOVA SAMIYA"},
        {"U2510057", "SAMANDAROV ABBOSBEK"},
        {"U2510058", "RAHMATJONOV BEHRUZ"},
        {"U2510059", "BAXTIYOROVA SHIRIN"},
        {"U2510060", "ISRAILOV BAXODIRXON"},
        {"U2510061", "XO'JAYEV XUMOYUN"},
        {"U2510062", "ISROILOV NURSULTON"},
        {"U2510063", "BOBOQULOVA DILSHODA"},
        {"U2510064", "YERZAKOV AKMAL"},
        {"U2510065", "SAIDAZIZOVA SHAXRIZODAXON"},
        {"U2510066", "XAFIZOV AMIR"},
        {"U2510067", "SHAROBIDDINOV SHOHJAHON"},
        {"U2510068", "TO'LQINOV AZIZBEK"},
        {"U2510069", "KIM ANNA"},
        {"U2510070", "RASULMUXAMEDOV ABDUJALIL"},
        {"U2510071", "YUNUSOV IZZATULLA"},
        {"U2510072", "VORONIN MIXAIL"},
        {"U2510073", "ORIFJONOV SHAXZODBEK"},
        {"U2510074", "XADJIAXMEDOVA HILOLABONU"},
        {"U2510075", "MIRZAYEV TOXIR"},
    };

    // CIE-25-04
    groupStudents["CIE-25-04"] = {
        {"U2510076", "KIM MAXIM"},
        {"U2510077", "HAMIDULLAYEV AKBARJON"},
        {"U2510078", "SHIROKIX GEORGIY"},
        {"U2510079", "YANA SEMIANIUTA"},
        {"U2510080", "ABDULQAYUMOV ABDUKARIM"},
        {"U2510081", "DUVANOV ARTYOM"},
        {"U2510082", "QAMBARALIYEV NURMUHAMMAD"},
        {"U2510083", "ALIJONOV OYATULLOH"},
        {"U2510084", "MUXAMEDOV ABDULMALIK"},
        {"U2510085", "SHERMUXAMEDOV BEKZOD"},
        {"U2510086", "KURBANOV KOMRON"},
        {"U2510087", "IRGASHEV AKMAL"},
        {"U2510088", "KAYRULLAEV ISLAMBEK"},
        {"U2510089", "QODIRALIYEV AZIMJON"},
        {"U2510090", "VAFOQULOV BAXODIR"},
        {"U2510091", "RASHIDOV ABDUJABBOR"},
        {"U2510092", "NOVIKOV YAROSLAV"},
        {"U2510093", "FAYZURAXMANOV SHAHRIYOR"},
        {"U2510094", "BOZOROV LAZIZ"},
        {"U2510095", "SOBIROVA RUXSORA"},
        {"U2510096", "IBRAGIMOV FARRUX"},
        {"U2510097", "RAXMONOV SANJAR"},
        {"U2510098", "FAYZULLAYEVA FARANGIZ"},
        {"U2510099", "QODIROV XOTAM"},
        {"U2510100", "FAYZIYEV MURODJON"},
    };

    // CIE-25-05
    groupStudents["CIE-25-05"] = {
        {"U2510101", "MANNOBOV ALISHER"},
        {"U2510102", "ASADOV AMIRXON"},
        {"U2510103", "SAYDINABIYEV SAIDAZIZXON"},
        {"U2510104", "PARPIYEV BAXTIYORJON"},
        {"U2510105", "ZARIFOV XUSAN"},
        {"U2510106", "XUSENOV SHOXRUX"},
        {"U2510107", "JO'RAYEV ABDURRAHMON"},
        {"U2510108", "KARIMOV SHERMUKHAMMAD"},
        {"U2510109", "JUMAYEV ULUG'BEK"},
        {"U2510110", "ZOXIDOV MIRAHMAD"},
        {"U2510111", "OVGANOV AZIZBEK"},
        {"U2510112", "SADULLAYEV JAVOHIR"},
        {"U2510113", "SUBHONOV OZODBEK"},
        {"U2510114", "SUPRUN DMITRIY"},
        {"U2510115", "NE'MATOV A'ZAMXON"},
        {"U2510116", "FAXRIDDINOV HUSNIDDIN"},
        {"U2510117", "SA'DULLAYEVA MOHIRAXON"},
        {"U2510118", "KIM DENIS"},
        {"U2510119", "AXMADJONOV FARRUHBEK"},
        {"U2510120", "MIRXANOV MIRSAID"},
        {"U2510121", "SADILLOYEV FARRUX"},
        {"U2510122", "ISMAILI KAMILLA"},
        {"U2510123", "RUSTAMOV ABDULLOH"},
        {"U2510124", "YOQUBJONOV ABDURAHIM"},
        {"U2510125", "BADRITDINOVA E'ZOZA"},
    };

    // CIE-25-06
    groupStudents["CIE-25-06"] = {
        {"U2510126", "XAMROKULOVA RAYHONA"},
        {"U2510127", "XAYDAROVA MALIKA"},
        {"U2510128", "ERGASHEVA GULASAL"},
        {"U2510129", "MURTAZAYEV AZIZBEK"},
        {"U2510130", "SODIKOV SAIDAMIRXON"},
        {"U2510131", "ISLAMOV XURSHID"},
        {"U2510132", "SULEYMANOV DANIEL"},
        {"U2510133", "KIM MAKSIM"},
        {"U2510134", "BOYMURATOVA KAMOLA"},
        {"U2510135", "MAXAMATJONOV SHOHRUXBEK"},
        {"U2510136", "GILMUTDINOV SHARIFULLO"},
        {"U2510137", "IDRISOV SHOHJAHON"},
        {"U2510138", "MUMINOV SUXROBBEK"},
        {"U2510139", "SIROJIDDINOV BEHRUZ"},
        {"U2510140", "XUDAYBERDIYEV SARDORBEK"},
        {"U2510141", "MO'MINJONOV AZIZBEK"},
        {"U2510142", "XAZRATQULOV ASLIDDIN"},
        {"U2510143", "RUSTAMOV ABDURAHMON"},
        {"U2510144", "SADULLAYEVA ALINA"},
        {"U2510145", "KALIMULLIN TIMUR"},
        {"U2510146", "TUROBJONOV BEHRUZ"},
        {"U2510147", "SHTEFLYA IRINA"},
        {"U2510148", "TAJIBAYEV ASAD"},
        {"U2510149", "ONISHENKO ALEKSEY"},
        {"U2510150", "ABRAROV BEGZOD"},
    };

    // CIE-25-07
    groupStudents["CIE-25-07"] = {
        {"U2510151", "TOSHPO'LATOVA E'ZOZA"},
        {"U2510152", "KARIMOVA MADINAXON"},
        {"U2510153", "MADRIMOVA ZAXRO"},
        {"U2510154", "BAXRITDINOV SHERZOD"},
        {"U2510155", "BAXTIYOROV SHAXRIYOR"},
        {"U2510156", "ISOQOV ULUG'BEK"},
        {"U2510157", "BEKTIMIROV MAHMUD"},
        {"U2510158", "ABDUGAFFOROVA SURAYYO"},
        {"U2510159", "ABDUKARIMOVA FARANGISXON"},
        {"U2510160", "YO'LDOSHEVA CHAROS"},
        {"U2510161", "MUXTORJONOV BEHZODBEK"},
        {"U2510162", "DAVRONOV DOSTONBEK"},
        {"U2510163", "KURBONOV ABDULLOH"},
        {"U2510164", "PULATOV AMIR"},
        {"U2510165", "KIM ROMAN"},
        {"U2510166", "NEMATOV FARRUX"},
        {"U2510167", "ESHONOV SHOHZOD"},
        {"U2510168", "XOLBOYEV ANVAR"},
        {"U2510169", "MAMADIYEVA AZIZA"},
        {"U2510170", "NORTOJIYEV OYBEK"},
        {"U2510171", "MURODKULOV NAZARBEK"},
        {"U2510172", "SERJANOV NURJAN"},
        {"U2510173", "AYNAQULOVA YASMINA"},
        {"U2510174", "NARZULLOYEV SHAHRILLO"},
        {"U2510175", "XALIMOV MUHAMMADJON"},
    };

    // CIE-25-08
    groupStudents["CIE-25-08"] = {
        {"U2510176", "SAMIG'JONOVA NAFISA"},
        {"U2510177", "PAK DEN"},
        {"U2510178", "BALTABAYEV BEHZOD"},
        {"U2510179", "HAMZAYEV FAZLIDDIN"},
        {"U2510180", "ABDULLAYEV SAID AKROM"},
        {"U2510181", "PIRMUXAMEDOVA MADINA"},
        {"U2510182", "ABDUMALIKOV ISKANDAR"},
        {"U2510183", "MAXSUDOV SUHROBBEK"},
        {"U2510184", "TESHAQULOV SHOHJAHON"},
        {"U2510185", "BAXTIYOROV JAMSHIDBEK"},
        {"U2510186", "TURABOV BOBUR"},
        {"U2510187", "RIZAYEV AMIR"},
        {"U2510188", "ISMOILOV ISKANDAR"},
        {"U2510189", "NIZAMUTDINOVA GUZALIYA"},
        {"U2510190", "YO'LDOSHEV ABDULLOH"},
        {"U2510191", "ISKANDAROV AZIZBEK"},
        {"U2510192", "UMEDOV FITRAT"},
        {"U2510193", "GLAZIRINA YELIZAVETA"},
        {"U2510194", "ABDIKAYUMOV ELBEK"},
        {"U2510195", "YUSUPOV ANVAR"},
        {"U2510196", "AZIMOV HUSANJON"},
        {"U2510197", "MUHAMMADIYEVA FARANGIZ"},
        {"U2510198", "FARXODOV AFRUZ"},
        {"U2510199", "KARIMOV SARDORBEK"},
        {"U2510200", "OBIDOV MUHAMMADSOLIH"},
    };

    // CIE-25-09
    groupStudents["CIE-25-09"] = {
        {"U2510201", "ZAYNIDDINOV FAZLIDDIN"},
        {"U2510202", "DYO DMITRIY"},
        {"U2510203", "XRIPCHENKO STANISLAV"},
        {"U2510204", "SOBIRJONOV AKBARSHOH"},
        {"U2510205", "DAVLATOV SHOXJAXON"},
        {"U2510206", "ABDULLOYEV XABIB"},
        {"U2510207", "SAIDAZIMOVA MAFTUNA"},
        {"U2510208", "RUZIYEV FIRDAVS"},
        {"U2510209", "XASANBOYEVA FARZONA"},
        {"U2510210", "KOBILJONOVA DILBAR"},
        {"U2510211", "JAMOLOV BILOL"},
        {"U2510212", "SHAYXULLIN MARAT"},
        {"U2510213", "MIRG'IYOSOV MIRAKBAR"},
        {"U2510214", "RO'ZIMURODOV SHAHRO'Z"},
        {"U2510215", "ALIBEKOV ABDULBORIY"},
        {"U2510216", "ABDURAZAKOV DAMIR"},
        {"U2510217", "INOYATOV BOBURSHOH"},
        {"U2510218", "MAXMUDOV JAVOHIR"},
        {"U2510219", "RAXIMOV SHAHBOZ"},
        {"U2510220", "ABDUVOXOBOV ABDULAZIZBEK"},
        {"U2510221", "AXMADJONOV SARVARJON"},
        {"U2510222", "SAIDTOXIROV SAIDJOVXAR"},
        {"U2510223", "MUXAMEDOV ABDULAZIZ"},
        {"U2510224", "KAN NIKITA"},
        {"U2510225", "LI MAKSIM"},
    };

    // CIE-25-10
    groupStudents["CIE-25-10"] = {
        {"U2510226", "NEMATOV DONIYOR"},
        {"U2510227", "ZYUBIN ARTYOM"},
        {"U2510228", "BABAJANOV ABDULAZIZ"},
        {"U2510229", "SODIQOV ABDUJALIL"},
        {"U2510230", "MIRZABAYEV XUSAN"},
        {"U2510231", "MOSPAN SOFIYA"},
        {"U2510232", "MELNIKOV DANIL"},
        {"U2510233", "KODIROV SHUXRAT"},
        {"U2510234", "ASENBAEV SALAMAT"},
        {"U2510235", "YUNUSOV EMIL"},
        {"U2510236", "ABDURAZZOQOV ABDULAZIZ"},
        {"U2510237", "POLYAKOV ALEKSANDR"},
        {"U2510238", "AXMADJONOV MUSLIMBEK"},
        {"U2510239", "SEYT-EMINOV SERVER"},
        {"U2510240", "XASANOV AMIR"},
        {"U2510241", "PALVANOVA NAZOKAT"},
        {"U2510242", "MAXMUDOV AL-QUDDUSXODJA"},
        {"U2510243", "URINBOYEV NODIRBEK"},
        {"U2510244", "MANSUROV AKBAR"},
        {"U2510245", "EGAMOV MUHAMMAD"},
        {"U2510246", "MAHAMATJONOV SARDORBEK"},
        {"U2510247", "OLIMOV JONIBEK"},
        {"U2510248", "RO'ZIQULOV NODIRBEK"},
        {"U2510249", "KIM KIRILL"},
        {"U2510250", "SAIDJANOV JAXONGIR"},
    };

    // CIE-25-11
    groupStudents["CIE-25-11"] = {
        {"U2510251", "JO'RAQULOV XURSHID"},
        {"U2510252", "XUDOYBERDIYEV DAMIR"},
        {"U2510253", "RUSTAMOVA MUNISA"},
        {"U2510254", "ABDURAXIMOVA GULRUX"},
        {"U2510255", "ABDUMANONOV ABDUMALIK"},
        {"U2510256", "AZADAYEV RAVSHAN"},
        {"U2510257", "JENISBAEV BEKTIMUR"},
        {"U2510258", "NAIMOV ABRORBEK"},
        {"U2510259", "YAXYOYEV ULUG'BEK"},
        {"U2510260", "NORBEKOV BEHRUZ"},
        {"U2510261", "ISAMUXAMMATOV ISFANDIYOR"},
        {"U2510262", "ZOIROV BEHRUZ"},
        {"U2510263", "ABDUMUTALOV ULUG'BEK"},
        {"U2510264", "XODJANOV DILSHOD"},
        {"U2510265", "KUZIYEV DONIYOR"},
        {"U2510266", "MELIBOYEV ILHOMJON"},
        {"U2510267", "ZARIFOV HUSNIDDIN"},
        {"U2510268", "GARAYEVA DIANA"},
        {"U2510269", "TOJIBOYEV ABUBAKR"},
        {"U2510270", "MUXAMADOV MAQSUDBEK"},
        {"U2510271", "SOBIROV JAXONGIR"},
        {"U2510272", "ABDULHAMIDOV UMIDJON"},
        {"U2510273", "IBRAGIMOV ANVAR"},
        {"U2510274", "KUNNAZAROV ADILBEK"},
        {"U2510275", "YAGNYAYEV RATMIR"},
    };

    // CIE-25-12
    groupStudents["CIE-25-12"] = {
        {"U2510276", "XUSHNAZAROV OYBEK"},
        {"U2510277", "MAMANIYOZOV ABDULLOH"},
        {"U2510278", "ABDUSAMATOV ABDULLOH"},
        {"U2510279", "ESHMAMATOV OG'ABEK"},
        {"U2510280", "SOLIKJONOV ABDULHAMID"},
        {"U2510281", "ORINBAEV KAMILBEK"},
        {"U2510282", "YAKUBOVA DILAFRUZ"},
        {"U2510283", "ABIDOV SHOHRUH"},
        {"U2510284", "UTEPBERGENOV BERDAX"},
        {"U2510285", "XASANOV BEHRUZ"},
        {"U2510286", "XUDOYBERDIYEV SARDORBEK"},
        {"U2510287", "TOLIBJONOV DILSHODBEK"},
        {"U2510288", "NURIDDINOV ABDULALIM"},
        {"U2510289", "OLIMJONOV NURMUHAMMAD"},
        {"U2510290", "ABDULLAYEV MURODULLA"},
        {"U2510291", "MAKSUMOVA NASIBA"},
        {"U2510292", "ISLAMOV FIRDAVS"},
        {"U2510293", "SHAISLAMOV SHAKHRUZ"},
        {"U2510294", "ARUTYUNYANTS VIKTORIA"},
    };
}
