#include "mainwindow.h"


static const QSettings::Format xmlFormat = QSettings::registerFormat("xml", &readSettingsXml, &writeSettingsXml);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString xmlFile = "C:/Users/ayesha/QtWorkspace/ayesha3" ;
    QMap<QString, QVariant> mapdef;
    int ret1 = createXml(xmlFile, mapdef);
    if(ret1)
        qDebug() << "xml File created";
  /*  Qmap< QString, QVariant> map;

   int ret2 = readXml(xmlFile,  map);
    if(ret2)
        qDebug() << "xml File is read into map Table";*/

    QString value1 = "write value";
    QString value2 = "read value";
    QString Element1 = "Monkey";
    QString Element2 = "Owl";

    int ret3 = writeXmlElement(xmlFile,Element1,value1);
    if(ret3)
        qDebug() << "Writing is done";

    int ret4 = readXmlElement(xmlFile,Element2,value2);
    if(ret4 == 0)
        qDebug() << "Read Complete";
    else if(ret4 == -1)
        qDebug() << "Element doesnt exist";
    else ;

    return a.exec();
}

int createXml(QString &fileName,QMap<QString, QVariant> &mapdef)
{

   // qSetGlobalQHashSeed(42); // set a fixed hash value
    QSettings settings(fileName,xmlFormat,0);
    QFile filename;
    qDebug() << "file exists :"  << (filename.exists(fileName));
      qDebug() << "file name :" << settings.fileName();

      /* ** PCA settings ** */
      mapdef.insert(" NAME123", "0.0.0.1");
      mapdef.insert("VERSION", "0.0.0.1");
       mapdef.insert("VERSION1", "0.0.0.1");
        mapdef.insert("VERSION2", "0.0.0.1");
     mapdef.insert("ID", "1");
      /* * PCA CAPABILITIES ** */
      mapdef.insert("CAPABILITIES/MODES/ANGLE","undefined");
      mapdef.insert("CAPABILITIES/MODES/TRACKING","undefined");
      mapdef.insert("CAPABILITIES/MODES/TRACKING/GEO_LOCK","undefined");
      mapdef.insert("CAPABILITIES/MODES/TRACKING/OBJECT_LOCK","undefined");
      mapdef.insert("CAPABILITIES/MODES/TRACKING/OBJECT_LOCK_AND_FOLLOW","undefined");
      mapdef.insert("CAPABILITIES/MODES/MAPPING","undefined");

      /**SENSOR1 settings**/
      mapdef.insert("SENSORS/SENSOR1/ID", "1");
      mapdef.insert("SENSORS/SENSOR1/NAME", "EH3150");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/TYPE", "EO");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/ZOOM/MIN_ZOOM", "1");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/ZOOM/MAX_ZOOM", "10");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/ZOOM/ZOOM_NUM_LEVELS", "10");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/ZOOM/TYPE", "O");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/FOV/MIN_FOV", "4.6");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/FOV/MAX_FOV", "53.4");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/FRAME_RATE", "30");
      mapdef.insert("SENSORS/SENSOR1/CAPABILITIES/RESOLUTION", "1280x720");
      /**GIMBAL settings ..???? to be made more detailed**/
      mapdef.insert("GIMBAL/GIMBAL1/ID","1");
      mapdef.insert("GIMBAL/GIMBAL1/CONNECTED_SENSORS","1");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION","R-P");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/LIMITS/R_MIN","-40");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/LIMITS/R_MAX","+40");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/LIMITS/P_MIN","-20");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/LIMITS/P_MAX","+60");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/ACTUATION","Brushless");
      mapdef.insert("GIMBAL/GIMBAL1/CAPABILITIES/CONFIGURATION/CONTROLLER","Alexmos");
      /**VEHICLE settings ... ***/
      mapdef.insert("VEHICLE_CONFIG/ID","1");
      mapdef.insert("VEHICLE_CONFIG/FLIGHT_CONTROLLER","Atom");
      mapdef.insert("VEHICLE_CONFIG/PROTOCOL","E-Link");
      mapdef.insert("VEHICLE_CONFIG/TYPE","FW");
      /**COMMUNICATION settings ***/
      mapdef.insert("COMM_CONFIG/PCA_PORT","10001");
      mapdef.insert("COMM_CONFIG/PROTOCOL","Elink");
      mapdef.insert("COMM_CONFIG/AP/IP","192.168.1.150");
      mapdef.insert("COMM_CONFIG/AP/PORT","20001");

      QMap<QString, QVariant>::iterator k;
      for (k = mapdef.end(); k != mapdef.begin(); --k)
      {
         settings.setValue(k.key(), k.value());
         qDebug() << "map:" << k.key();
      }


      settings.sync();

   //   settings.setValue("PCA/size1", "000");
       QStringList keys = settings.allKeys();
       int i;
       for(i = 0; i <4; i++)
       {
           qDebug() << settings.value(keys.value(i)).toString() ;
           qDebug() << "key :"<< keys.value(i);
       }

       qDebug() << settings.value("monkey/tail/size2") ;
        qDebug() << settings.contains("monkey/tail/") ;
       qDebug() << settings.value("monkey/tail/size1").toString();
       qDebug() << settings.value("monkey/tail/fullScreen2").toString() ;

       qDebug() << settings.value("monkey/size2").toString();

       qDebug() << settings.value("monkey2/fullScreen1").toString() ;

       qDebug() << settings.value("monkey2/size1").toString();
       qDebug() << settings.value("monkey2/fullScreen2").toString() ;

       qDebug() << settings.value("monkey2/size2").toString();
 qDebug() <<"hash :" <<settings.value("SENSORS/SENSOR1/ID").toInt();

      return 0;


}

int readXml(QString &fileName, QMap<QString, QVariant> &map){}
int writeXmlElement(QString &fileName, QString &element, QString &value){}
int readXmlElement(QString &fileName,  QString &element, QString &value){}
