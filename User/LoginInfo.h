#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<filesystem>
#include<ctime>
#include<cstdlib>
class LoginInfo
{
public:
	std::string UsernameInformation;
	std::string PasswordInformation;
	//std::string encryptUserInfo(std::string Info);
	//std::string decryptUserInfo(std::string encryptedInfo);
};
//int key = (int)rand() % 5;
//int&k = d;

void saveUserInfoToFile(std::vector<LoginInfo>& Informationvector, const std::string& filename);
std::vector<LoginInfo> loadUserInfoFromFile(const std::string& filename);
//std::string encryptUserInfo();
//std::string decryptUserInfo();
std::string encryptUserInfo(std::string Info, int& key);
std::string decryptUserInfo(std::string encryptedInfo, int& key);

