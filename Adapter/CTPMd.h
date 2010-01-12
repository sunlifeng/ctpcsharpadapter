// CTP.h
#include <vcclr.h>

#include <iostream>

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "CSApiStruct.h"

#pragma once

using namespace System;
using namespace std;
using namespace System::Runtime::InteropServices;

namespace CTP {

#include ".\ThostTraderApi\ThostFtdcMdApi.h"


	CThostFtdcMdApi* pUserApi;

	// 配置参数
	char FRONT_ADDR[] = "tcp://asp-sim2-md1.financial-trading-platform.com:26213";		// 前置地址
	TThostFtdcBrokerIDType	BROKER_ID = "2030";				// 经纪公司代码
	TThostFtdcInvestorIDType INVESTOR_ID = "00092";			// 投资者代码
	TThostFtdcPasswordType  PASSWORD = "888888";			// 用户密码
	char *ppInstrumentID[] = {"cu0907", "cu0909"};			// 行情订阅列表
	int iInstrumentID = 2;								// 行情订阅数量

	int iRequestID = 0;  // 请求编号

	public interface class CTPMdSpi
	{
	public:
		///错误应答
		virtual void OnRspError(CSCThostFtdcRspInfoField^ pRspInfo,
			int  nRequestID, bool bIsLast);
		virtual void OnFrontDisconnected(int nReason);
		virtual void OnHeartBeatWarning(int nTimeLapse);
		virtual void OnFrontConnected();
		virtual void OnRspUserLogin(CSCThostFtdcRspUserLoginField^ pRspUserLogin,	CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspSubMarketData(CSCThostFtdcSpecificInstrumentField^ pSpecificInstrument, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspUnSubMarketData(CSCThostFtdcSpecificInstrumentField^ pSpecificInstrument, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRtnDepthMarketData(CSCThostFtdcDepthMarketDataField^ pDepthMarketData);
	};

	public ref class CTPConfig
	{
	public:
		// 配置参数 以下参数清参考原始C++ API 文档
		// 前置地址
		String  ^FRONT_ADDR;
		// 经纪公司代码
		String	 ^BROKER_ID ;
		// 投资者代码
		String  ^INVESTOR_ID ;	
		// 用户密码
		String  ^PASSWORD;	
		// 合约代码
		String  ^INSTRUMENT_ID;			
		// 行情订阅列表
		array<String ^> ^  ppInstrumentID;	
		// 行情订阅数量
		int iInstrumentID ;	
		// 请求编号
		int iRequestID;  
		//double	LIMIT_PRICE;
		//char	DIRECTION;

		CTPMdSpi^  ctpSpi;  
	};

	public   class CMdSpi : public CThostFtdcMdSpi
	{
	public:
		///错误应答
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
			int nRequestID, bool bIsLast);

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		virtual void OnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		///@param nTimeLapse 距离上次接收报文的时间
		virtual void OnHeartBeatWarning(int nTimeLapse);

		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();

		///登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///订阅行情应答
		virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///取消订阅行情应答
		virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///深度行情通知
		virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


		gcroot<CTPConfig^>   ctpConfig;

	private:
		void ReqUserLogin();
		void SubscribeMarketData();
		// 
		bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
	};

	public ref class CTPMDAdapter
	{
	public:
		int Start()
		{
			pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
			CThostFtdcMdSpi* pUserSpi = new CMdSpi();
			((CMdSpi*)pUserSpi)->ctpConfig=this->ctpConfig;

			pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
			pUserApi->RegisterFront(FRONT_ADDR);					// connect
			pUserApi->Init();

			pUserApi->Join();

			return 0;
		}
		void Config(CTPConfig^   ctpConfig)
		{
			this->ctpConfig=ctpConfig;
			char* abc;
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpConfig->FRONT_ADDR)).ToPointer();
			strcpy_s(FRONT_ADDR,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpConfig->BROKER_ID)).ToPointer();
			strcpy_s(BROKER_ID,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpConfig->INVESTOR_ID)).ToPointer();
			strcpy_s(INVESTOR_ID,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpConfig->PASSWORD)).ToPointer();
			strcpy_s(PASSWORD,abc);
			for( int i=0 ;i<ctpConfig->ppInstrumentID->Length;i++)
			{
				ppInstrumentID[i]=( char*)   (Marshal::StringToHGlobalAnsi(ctpConfig->ppInstrumentID[i])).ToPointer();
			}
			iInstrumentID=ctpConfig->iInstrumentID;

		}
		void ReqUserLogin()
		{
			cerr << __FUNCTION__ << endl;
		}
		void SubscribeMarketData()
		{

		}
		// 
		bool IsErrorRspInfo(CSCThostFtdcRspInfoField ^pRspInfo)
		{
			return true;
		}
		CTPConfig^   ctpConfig;
	private:
	};


}
