#include "LoginInfo.h"
#include<string>
#include<vector>
#include<fstream>
#include<filesystem>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<random>//for generating random number
//std::random_device rd; // Seed the engine with a truly random value
//std::mt19937 generator(rd()); // Mersenne Twister 19937 generator
//
//// Define a distribution (e.g., uniform distribution between 1 and 100)
//std::uniform_int_distribution<int> distribution(1, 5);
//
//// Generate random numbers
//int key = distribution(generator);
int key = (int)rand() % 5;
void saveUserInfoToFile(std::vector<LoginInfo>& Informationvector, const std::string& filename)
{
	std::ofstream outfile(filename, std::ios::app | std::ios::binary);//output to the file i.e save to the file
	//outfile << Informationvector.size()<<'\n';
	for (LoginInfo& Info : Informationvector) {
		std::string UsersInformation = Info.UsernameInformation;
		std::string PasswordInformation = Info.PasswordInformation;

		std::string encryptedUserInformation = encryptUserInfo(UsersInformation, key);
		std::string encryptedPasswordInformation = encryptUserInfo(PasswordInformation, key);
		//UserInformation.replace(UserInformation.begin(), UserInformation.end(), ' ', '_');
		//PasswordInformation.replace(PasswordInformation.begin(), PasswordInformation.end(), ' ', '_');

		//outfile << UserInformation<<'\n' << PasswordInformation<<'\n';
		outfile << encryptedUserInformation << '\n' << encryptedPasswordInformation << '\n';


	}

}

std::vector<LoginInfo> loadUserInfoFromFile(const std::string& filename)
{
	if (!std::filesystem::exists(filename)) {
		return std::vector<LoginInfo>();

	}
	std::vector<LoginInfo> Informationvector;
	std::ifstream infile(filename);

	//int a;
	//infile >> a;
	// (int i = 0; i < a; i++) {
	while (!infile.eof()) {
		std::string encryptedUserInformation;
		std::string encryptedPasswordInformation;
		//encryptedUserInfo(UserInformation);
		infile >> encryptedUserInformation;
		infile >> encryptedPasswordInformation;
		//UserInformation.replace(UserInformation.begin(), UserInformation.end(), ' ', '_');
		//PasswordInformation.replace(PasswordInformation.begin(), PasswordInformation.end(), ' ', '_');
		//std::string UserInfo= this->decryptUserInfo(UserInformation)
		std::string UserInformation = decryptUserInfo(encryptedUserInformation, key);
		std::string PasswordInformation = decryptUserInfo(encryptedPasswordInformation, key);
		Informationvector.push_back(LoginInfo{ UserInformation, PasswordInformation });
	}
	//}
	return Informationvector;
}
std::string encryptUserInfo(std::string Info, int& key) {
	//int key = (int)rand() % 5;//(int)rand() / 5;

	for (int i = 0; (i < 100 && Info[i] != '\0'); i++) {
		Info[i] = Info[i] - key;
	}
	return Info;
}
std::string decryptUserInfo(std::string encryptedInfo, int& key)
{

	for (int i = 0; (i < 100 && encryptedInfo[i] != '\0'); i++) {
		encryptedInfo[i] = encryptedInfo[i] + key;
	}
	return encryptedInfo;
}
