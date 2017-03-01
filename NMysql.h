#ifndef MYMYSQL_H
#define MYMYSQL_H
#include <windows.h>
#include <mysql.h>
#include <QStandardItemModel>
#include <QStringList>
#include <string.h>
#include <vector>
class NMysql
{
public:
	NMysql(QString);
	const char *get_error();
	int mysql_connect(QString ip, QString user, QString db);
	void mysql_DisConnet();
	int input_sql(const char *SQL);
	int get_clients();
private:
	QStringList			 list_client;
	//std::vector<QString> m_result;
	QString				 m_name;
	MYSQL_RES*			 m_result;
	MYSQL *				 m_connection;
	MYSQL				 m_mysql;
	char				 m_buf[1024];
				
};

#endif // MYMYSQL_H
