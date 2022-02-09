#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMap>
#include <QFile>
#include <QCoreApplication>
class WeatherTool
{
private:
    std::map<QString, QString> m_mapCity2Code;
public:
    WeatherTool(){
            //��ȡ��ǰ�������е�·��
            QString fileName = QCoreApplication::applicationDirPath();
            //����������Ϣ�ռ��Ķ���
            QJsonParseError err;
            //�����ļ����ڵ�·������Ϊcitycode-2019-08-23.json������Ŀ�ļ����£�Ҳ���Խ������Ƶ�
            //��Ŀ���е�Ŀ¼�£��Ͳ���Ҫ��ô�ȷ�������Ŀ¼
            fileName += "/../../Weather-forecast/citycode-2021-7-21.json";
            QFile file(fileName);
            //���ļ�
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            QByteArray json = file.readAll();
            file.close();
            //��ȡJson����
            QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &err);
            //��ȡ�����б�����
            QJsonArray citys = jsonDoc.array();
            for(int i=0;i<citys.size();i++)
            {
                QString code = citys.at(i).toObject().value("city_code").toString();
                QString city = citys.at(i).toObject().value("city_name").toString();
                if(code.size()>0){
                    m_mapCity2Code.insert(std::pair<QString,QString>(city,code));
                }
            }
        }

    //���ز�����[��city��]�����ݳ�������ֱ�ӵõ����д���
    QString operator[](const QString& city){
            std::map<QString,QString>::iterator it = m_mapCity2Code.find(city);
            if(it==m_mapCity2Code.end()){//��ȴ���û���ҵ�
                it = m_mapCity2Code.find(city+u8"��");
            }
            if(it==m_mapCity2Code.end()){//��ȴ���û���ҵ�
                it = m_mapCity2Code.find(city+u8"��");
            }
            if(it!=m_mapCity2Code.end()){
                //�ҵ�ֱ�ӷ��س��д���
                return it->second;
            }
            //û�ҵ�����9��0
            return "000000000";
    }

};

#endif // WEATHERTOOL_H
