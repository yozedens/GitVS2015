#include"handWriting.h"



bool compCfs(Cfloatstr a, Cfloatstr b)
{
	if (a.flo < b.flo)
		return 1;
	else
		return 0;
}

void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

vector<string> readContent(char* filePath)
{	
	vector<string> files;
	getFiles(filePath, files);//获取该路径下的所有文件

	//for (int i = 0; i < files.size(); i++)
	//{
	//	cout << files[i] << endl;
	//}
	return files;
}

vector<int> img2vector(string fileName)
{
	//字符间无空格
	//cout << fileName << endl;

	ifstream file(fileName);
	string str;
	int lenStr;
	vector<int> vecImg;
	while (file>>str)
	{
		lenStr = str.size();
		for (int i = 0; i < lenStr; i++)
		{
			vecImg.push_back(str[i] - 48);
			//cout <<"str[i]: "<< str[i] << endl;
		}
	}
	/*for (auto data : vecImg)
	{
		cout << data << " ";
	}
	cout << endl;*/
	return vecImg;

}

vector<int> img2vector2(string fileName)
{
	//字符间有空格
	//cout << fileName << endl;

	ifstream file(fileName);
	int num;
	vector<int> vecImg;
	while (file >> num)
	{
		vecImg.push_back(num);
		cout << num << endl;
	}
	file.close();
	return vecImg;

}

vector<vector<int>> getDataSet(char* filePath, vector<string> &labels)
{
	vector<string> files;
	//labels = files;

	vector<vector<int>> dataSet;
	files = readContent(filePath);
	int len = files.size();
	for (int i = 0; i < len; i++)
	{
		//cout << files[i].substr(files[i].find_last_of('\\'),3) << endl;
		//cout << files[i].substr(17, 2) << endl;

		labels.push_back(files[i].substr(files[i].find_last_of('\\'), 3));//用文件名中的特定字符标记标签
		dataSet.push_back(img2vector(files[i]));
	}
	return dataSet;
}

void matrix2file(vector<vector<int>> matrix, string fileName)
{
	ofstream file(fileName);
	int lenRow = matrix.size();
	int lenColumn = matrix[0].size();
	for (auto dataRow : matrix)
	{
		for (auto data : dataRow)
		{
			//cout << data << endl;
			file << data << " ";
		}
		file << endl;
	}
}