#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int numsOfNetPoints;//����ڵ�����
int numsOfNetRoads;//��·����
int numsOfUserPoints;//���ѵ�����
int priceOfHoster;//�������۸�
int valueNow = 0;//��ǰ�۸�
int level = 2;//���������
float percentage = 0.7;//���ո���

vector<string> split(string str, string pattern){
    vector<string> ret;
    if (pattern.empty()) return ret;
    size_t start = 0, index = str.find_first_of(pattern, 0);
    while (index != str.npos)	{
        if (start != index)
            ret.push_back(str.substr(start, index - start));
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty())
        ret.push_back(str.substr(start));
        return ret;
}

int main()
{
    ifstream readMe("./valueAndPrice.txt");
    if(!readMe.is_open()){
        cout <<"Read failure" << endl;
    }
    string readySingleLine;
    getline(readMe, readySingleLine);
    vector<string> listLine = split(readySingleLine, " ");
    numsOfNetPoints = atoi(listLine.at(0).c_str());
    numsOfNetRoads = atoi(listLine.at(1).c_str());
    numsOfUserPoints = atoi(listLine.at(2).c_str());

    getline(readMe, readySingleLine);/*��ȡһ�п���*/
    getline(readMe, readySingleLine);
    priceOfHoster = atoi(readySingleLine.c_str());

    getline(readMe, readySingleLine);/*��ȡһ�п���*/

    /*��ʼ��ʼ����������*/
    int userPointRecord[numsOfUserPoints];//���ѵ��¼
    int userPointNeeds[numsOfUserPoints];//���ѵ�����
    int matrixOfRoadSize[numsOfNetPoints][numsOfNetPoints];
    int matrixOfRoadPrice[numsOfNetPoints][numsOfNetPoints];
    for (int i=0; i<numsOfNetPoints; i++){
        for (int j=0; j<numsOfNetPoints; j++){
            matrixOfRoadSize[i][j] = 0;
            matrixOfRoadPrice[i][j] = 0;
        }
    }

    for (int i=0; i<numsOfUserPoints; i++){
        userPointRecord[i] = 0;
        userPointNeeds[i] = 0;
    }

    /*��ʼ����۸�������Ϣ*/

    do{
        getline(readMe, readySingleLine);
        if (readySingleLine.empty()){
            break;
        }else{
            listLine = split(readySingleLine, " ");
            int x = atoi(listLine.at(0).c_str());
            int y = atoi(listLine.at(1).c_str());
            int roadSize = atoi(listLine.at(2).c_str());
            int roadValue = atoi(listLine.at(3).c_str());
            matrixOfRoadSize[x][y] = roadSize;
            matrixOfRoadPrice[x][y] = roadValue;
        }
    }while(true);

    /*�������ѽڵ�*/
    for (int i=0; i<numsOfUserPoints; i++){
        getline(readMe, readySingleLine);
        listLine = split(readySingleLine," ");
        userPointRecord[i] = atoi(listLine.at(1).c_str());
        userPointNeeds[i] = atoi(listLine.at(2).c_str());
    }

    valueNow = numsOfUserPoints * priceOfHoster;

    while(true){
        vector<vector<int>> treeRecord;/*��¼ĳһ����ѡ�����Ӱ������ļ������ѵ㣬ͬʱ�ڸ��е�0λ�ü�¼�������*/
        vector<vector<int>> userRootRecord;/*��¼ĳ���ѵ��������Щ�ڵ�*/
        for(int i=0; i<numsOfNetPoints;i++){
            vector<int> newVector;
            newVector.push_back(0);/*0λ�ü�¼���Ǳ����ǵĴ���*/
            treeRecord.push_back(newVector);
        }
        for(int i=0; i<numsOfUserPoints;i++){
            vector<int> newVector;
            userRootRecord.push_back(newVector);
        }



        /*���Ϊlevelʱ����ÿһ���ѵ����ѭ��������������Ϣ���ر��棬ʹ��һ�μ�¼����Ϣ����ɾ��*/
        for (int eachUserPoint=0; eachUserPoint<numsOfUserPoints; eachUserPoint++){
            /*userPointRecord[eachUserPoint] ��ÿһ���ѵ�����*/
            /*userPointNeeds[eachUserPoint] ��˳�������ѵ���������*/
            treeRecord.at(userPointRecord[eachUserPoint]).at(0) += 1; /*ÿһ����ڵ�Ľ������+1*/
            vector<int> treeCreate;/*���ڼ�¼�ȴ���ǰ�ҵ�Ľڵ�*/
            treeCreate.push_back(userPointRecord[eachUserPoint]);/*�ȴ���ǰ�ҵ������*/
            int tempFlag[numsOfNetPoints][numsOfNetPoints];    /*�����������������������������ĵ㽫����Ϊ0*/
            for (int i=0; i<numsOfNetPoints; i++){
                for (int j=0; j<numsOfNetPoints; j++){
                    tempFlag[i][j] = matrixOfRoadPrice[i][j];
                }
            }

            /*���ѵ�Ϊxʱ��Ϊ�����ѵ������������ѭ��*/
            for(int nowLevel=1; nowLevel<level; nowLevel++){
                vector<int> thisTimeSelect;

                /*����������Ϊxʱ��Ϊ�������ڵ����ѭ��*/
                for(int eachWaitting = 0; eachWaitting<(int)treeCreate.size();eachWaitting++){

                    /*���������Ľڵ�Ϊxʱ��Ϊ���е��н���ѭ��*/
                    /*treeCreate->at(eachWatting) ��ʵ�ʴ��ҵ������*/
                    for(int col=0; col<numsOfNetPoints; col++){
                        if(tempFlag[treeCreate.at(eachWaitting)][col] > 0){  /*����������ͨ·��δ���ʹ�ʱ��ѹջ������������Ϊ�ѷ���*/
                            thisTimeSelect.push_back(col); /*���ʵ���һ���ڵ�ѹջ*/
                            treeRecord.at(col).at(0) ++; /*������Ӱ��ڵ���++*/
                            treeRecord.at(col).push_back(userPointRecord[eachUserPoint]); /*����Ӱ��ĸ��ڵ��Ž���ѹջ*/
                            userRootRecord.at(userPointRecord[eachUserPoint]).push_back(col);
                            for(int row=0; row<numsOfNetPoints;row++){/*�����е�ͨ���˵��·������Ϊ�ѷ���*/
                                tempFlag[row][col] = 0;
                            }
                        }
                    }
                }
                treeCreate.clear();
                /*Ϊ��һ�����ı�����������*/
                for(int col=0; col<thisTimeSelect.size(); col++){
                    treeCreate.push_back(thisTimeSelect.at(col));
                }
                thisTimeSelect.clear();

            }
        }

        /*�Ͻ�˹����*/

    }


    return 0;
}
