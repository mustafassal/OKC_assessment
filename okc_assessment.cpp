#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string FILE_NAME = "shots_data.csv";

void getNumberOfEnteries(int& teamA, int& teamB)
{
	fstream file;
	file.open(FILE_NAME);
	string row;

	while (getline(file, row))
	{
		if (row[5] == 'A')
			teamA++;
		if (row[5] == 'B')
			teamB++;
	}
}
void getShotInfo(vector<double>& xArray, vector<double>& yArray, vector<bool>& shotMade)
{
	fstream file;
	file.open(FILE_NAME);
	string row;

	while (getline(file, row))
	{
		if (row[0] == 't')
			continue;
		
		string x_str;
		string y_str;
		int i = 7;
		while (row[i] != ',')
		{
			x_str += row[i];
			i++;
		}
		i++;
		while (row[i] != ',')
		{
			y_str += row[i];
			i++;
		}
		i++;
		if (row[i] == '0')
			shotMade.push_back(false);
		else if(row[i] == '1')
			shotMade.push_back(true);

		xArray.push_back(stod(x_str));
		yArray.push_back(stod(y_str));
	}
}

bool isCornerThree(double x, double y)
{
	if (y <= 7.8)
	{
		if (x > 22.0)
			return true;
		else
			return false;
	}

	return false;
}
bool isNonCornerThree(double x, double y)
{
	if (y > 7.8)
	{
		if ((x * x) + (y * y) > (23.75 * 23.75))
			return true;
		else
			return false;
	}

	return false;
}


int main() // close files
{
	int teamA_totalAttempted = 0;
	int teamB_totalAttempted = 0;
	getNumberOfEnteries(teamA_totalAttempted, teamB_totalAttempted);
	
	int teamA_C3Made = 0;
	int teamB_C3Made = 0;

	int teamA_NC3Made = 0;
	int teamB_NC3Made = 0;

	int teamA_2PTMade = 0;
	int teamB_2PTMade = 0;

	int teamA_C3Attempted = 0;
	int teamB_C3Attempted = 0;

	int teamA_NC3Attempted = 0;
	int teamB_NC3Attempted = 0;

	int teamA_2PTAttempted = 0;
	int teamB_2PTAttempted = 0;


	vector<double> shotXCoords;
	vector<double> shotYCoords;
	vector<bool> shotMade;

	getShotInfo(shotXCoords, shotYCoords, shotMade);

	for (int i = 0; i < teamA_totalAttempted + teamB_totalAttempted; i++)
	{
		if (i < teamA_totalAttempted)
		{
			if (isCornerThree(shotXCoords[i], shotYCoords[i]))
			{
				teamA_C3Attempted++;

				if (shotMade[i] == true)
					teamA_C3Made++;
			}
			else if (isNonCornerThree(shotXCoords[i], shotYCoords[i]))
			{
				teamA_NC3Attempted++;

				if (shotMade[i] == true)
					teamA_NC3Made++;
			}
			else
			{
				teamA_2PTAttempted++;

				if (shotMade[i] == true)
					teamA_2PTMade++;
			}
		}
		else
		{
			if (isCornerThree(shotXCoords[i], shotYCoords[i]))
			{
				teamB_C3Attempted++;

				if (shotMade[i] == true)
					teamB_C3Made++;
			}
			else if (isNonCornerThree(shotXCoords[i], shotYCoords[i]))
			{
				teamB_NC3Attempted++;

				if (shotMade[i] == true)
					teamB_NC3Made++;
			}
			else
			{
				teamB_2PTAttempted++;

				if (shotMade[i] == true)
					teamB_2PTMade++;
			}
		}
	}

	cout << "TEAM A PERCENTAGES:" << endl;

	cout << "2PT ATTEMPTS: " << (double) teamA_2PTAttempted / teamA_totalAttempted << endl;
	cout << "C3 ATTEMPTS: " << (double) teamA_C3Attempted / teamA_totalAttempted << endl;
	cout << "NC3 ATTEMPTS: " << (double) teamA_NC3Attempted / teamA_totalAttempted << endl;
	cout << endl;
	cout << "2PT eFG: " << (teamA_2PTMade + (.5 * (teamA_NC3Made + teamA_C3Made))) / teamA_totalAttempted << endl;
	cout << "C3 eFG: " << (teamA_C3Made + (.5 * (teamA_NC3Made + teamA_C3Made))) / teamA_totalAttempted << endl;
	cout << "NC3 eFG: " << (teamA_NC3Made + (.5 * (teamA_NC3Made + teamA_C3Made))) / teamA_totalAttempted << endl;

	cout << "--------------" << endl;

	cout << "TEAM B PERCENTAGES:" << endl;

	cout << "2PT ATTEMPTS: " << (double)teamB_2PTAttempted / teamB_totalAttempted << endl;
	cout << "C3 ATTEMPTS: " << (double)teamB_C3Attempted / teamB_totalAttempted << endl;
	cout << "NC3 ATTEMPTS: " << (double)teamB_NC3Attempted / teamB_totalAttempted << endl;
	cout << endl;
	cout << "2PT eFG: " << (teamB_2PTMade + (.5 * (teamB_NC3Made + teamB_C3Made))) / teamB_totalAttempted << endl;
	cout << "C3 eFG: " << (teamB_C3Made + (.5 * (teamB_NC3Made + teamB_C3Made))) / teamB_totalAttempted << endl;
	cout << "NC3 eFG: " << (teamB_NC3Made + (.5 * (teamB_NC3Made + teamB_C3Made))) / teamB_totalAttempted << endl;
}

