#include <string.h>
#include "NMysql.h"
#include <QMessageBox>

NMysql::NMysql(QString str) :m_name(str),m_connection(NULL)
{
	mysql_init(&m_mysql);

}

int NMysql::mysql_connect(QString ip,QString user,QString db)
{
	m_connection = mysql_real_connect(&m_mysql, ip.toUtf8().data(),
		user.toUtf8().data(),
		user.toUtf8().data(),
		db.toUtf8().data(),
		0, 0, 0);
	if (m_connection == NULL)
	{
		strcpy(m_buf, mysql_error(&m_mysql));
		return -1;
	}
	else
	{
		mysql_query(m_connection, QString("set names utf8").toUtf8().data());
		return 0;
	}

}

const char *NMysql::get_error()
{
	return m_buf;
}

void NMysql::mysql_DisConnet()
{
	if (m_connection)
	{
		mysql_close(m_connection);
		m_connection = NULL;
	}
}

int NMysql::input_sql(const char *SQL)
{
	if (mysql_query(m_connection, SQL) != 0)
	{
		memset(m_buf, 0, sizeof(m_buf));
		strcpy(m_buf, mysql_error(&m_mysql));
		return -1;
	}
	return 0;
}

int NMysql::get_clients()
{	

	m_result = mysql_store_result(m_connection);
	if (m_result == NULL)
	{
		memset(m_buf, 0, sizeof(m_buf));
		strcpy(m_buf, mysql_error(&m_mysql));
		return -1;
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_result)) != NULL)
	{
		list_client.push_back(row[0]);
	}

	mysql_free_result(m_result);//释放通过mysql_store_result函数分配的内存空间
	return 0;
}
