#include <iostream>
#include <string>
using namespace std;
enum enPlayer { Computer = 0, Player = 1, NoWinner = 2 };
enum enGame { Stone = 1, Paper = 2, Scissors = 3 };
struct stResultRound {
	short	NumOFRound;
	enGame	PlayerChoise;
	enGame	ComputerChoise;
	enPlayer Winner;
};
struct stGameResult {
	short	NumOFRoundsGame;
	short	ScorePlayer;
	short ScoreComputer;
	short	Drawtimes;
	string WinnerName;
	enPlayer Winner;
};
int ReadNumberInRange(int From, int To, string Message = "ENTER NUMBER") {
	int NUM;
	do {
		cout << Message << " FROM " << to_string(From) << " TO " << to_string(To) << ": ";
		cin >> NUM;
	} while (NUM < From || NUM > To);
	return NUM;
}
int RandomNumber(int From, int To) {
	return (rand() % (To - From + 1)) + From;
}
enPlayer CheckWinnerRound(enGame PlayerChoise, enGame ComputerChoise) {
	if ((PlayerChoise == ComputerChoise)
		) {
		return enPlayer::NoWinner;
	}
	else
		if ((PlayerChoise == enGame::Stone && ComputerChoise == enGame::Paper) ||
			(PlayerChoise == enGame::Paper && ComputerChoise == enGame::Scissors) ||
			(PlayerChoise == enGame::Scissors && ComputerChoise == enGame::Stone)
			) {
			return enPlayer::Computer;
		}
		else return enPlayer::Player;
}
string GetWinnerName(enPlayer Winner) {
	switch (Winner)
	{
	case enPlayer::Computer:
		return "Computer";
	case enPlayer::Player:
		return "Player";
	case enPlayer::NoWinner:
		return "NoWinner";
	default:
		return "NoWinner";
	}
}
void ChangeScreen(enPlayer Winner) {
	switch (Winner)
	{
	case enPlayer::Computer:
		system("color 4F");
		break;
	case enPlayer::Player:
		system("color 2F");
		break;
	case enPlayer::NoWinner:
		system("color 6F");
		break;
	default:
		break;
	}
}
string GetChoiseName(enGame Game) {
	switch (Game)
	{
	case enGame::Stone:
		return "Stone";
	case enGame::Paper:
		return "Paper";
	case enGame::Scissors:
		return "Scissors";
	default:
		return "Stone";
	}
}
void GameOver() {
	cout << "\t\t\t" << "##############################################################" << endl;
	cout << "\t\t\t" << "########################## GameOver ##########################" << endl;
	cout << "\t\t\t" << "##############################################################" << endl;
}
string CheckWinnerGame(stGameResult &GameResult) {
	if (GameResult.ScorePlayer == GameResult.ScoreComputer) {
		GameResult.Winner = enPlayer::NoWinner;
		return "No Winner";
	}
	else if (GameResult.ScorePlayer > GameResult.ScoreComputer)
	{
		GameResult.Winner = enPlayer::Player;
		return "Player";
	}
	else {
		GameResult.Winner = enPlayer::Computer;
		GameOver();
		return "Computer";
	}
}
void ShowResultRound(stResultRound& ResultRound) {
	cout << "########################################################" << endl;
	cout << "######################  Round[" << ResultRound.NumOFRound << "]  ######################" << endl;
	cout << "Player Choise: \t" << GetChoiseName(ResultRound.PlayerChoise) << endl;
	cout << "Computer Choise: \t" << GetChoiseName(ResultRound.ComputerChoise) << endl;
	cout << "Winner: \t" << GetWinnerName(ResultRound.Winner) << endl;
	cout << "########################################################" << endl;
}
void ShowResultGame(stGameResult& GameResult) {
	cout << endl << endl << endl;
	GameResult.WinnerName = CheckWinnerGame(GameResult);
	ChangeScreen(GameResult.Winner);
	cout << endl;
	cout << "\t\t\t" << "##############################################################" << endl;
	cout << "\t\t\t" << "###################### [ GAME RESULTS ] ######################" << endl;
	cout << "\t\t\t" << "Rounds: \t" << GameResult.NumOFRoundsGame << endl;
	cout << "\t\t\t" << "Player won times: \t" << GameResult.ScorePlayer << endl;
	cout << "\t\t\t" << "Computer won times: \t" << GameResult.ScoreComputer << endl;
	cout << "\t\t\t" << "Draw times: \t" << GameResult.Drawtimes << endl;
	cout << "\t\t\t" << "Winner: \t" << GameResult.WinnerName << endl;
	cout << "\t\t\t" << "##############################################################" << endl;
}
void PlayGame(short NumOFRoundsGame) {
	stResultRound ResultRound;
	stGameResult GameResult;
	GameResult.ScorePlayer = 0;
	GameResult.ScoreComputer = 0;
	GameResult.Drawtimes = 0;
	GameResult.NumOFRoundsGame = NumOFRoundsGame;
	for (int i = 1; i <= NumOFRoundsGame; i++)
	{
		cout << "Round [" << i + 1 << "] begins:" << endl;
		ResultRound.PlayerChoise = (enGame)ReadNumberInRange(1, 3, "ENTER YOUR CHOOSE: [1]:STONE [2]:PAPER [3]:SCISSORS ?");
		ResultRound.ComputerChoise = (enGame)RandomNumber(1, 3);
		ResultRound.Winner = CheckWinnerRound(ResultRound.PlayerChoise, ResultRound.ComputerChoise);
		ResultRound.NumOFRound = i;
		if (ResultRound.Winner == enPlayer::Player) {
			GameResult.ScorePlayer++;
		}
		else  if (ResultRound.Winner == enPlayer::Computer) {
			GameResult.ScoreComputer++;
		}
		else {
			GameResult.Drawtimes++;
		}
		ShowResultRound(ResultRound);
	}

	ShowResultGame(GameResult);
}
void ResetScreen() {
	system("cls");
	system("color 0F");

}
void SartGame() {
	int IsFinish = 1;
	while (IsFinish) {
		ResetScreen();
		short NumOFRoundsGame = ReadNumberInRange(1, 10, "PLEASE ENTER Num OF Rounds OF Game(from 1 to 10): ");
		PlayGame(NumOFRoundsGame);
		cout << endl << endl;
		cout << "DO YOU WANT TO PLAY AGAIN? [0]:No,[1]Yes? ";
		cin >> IsFinish;
		if (IsFinish != 1)break;
	}

}
int main()
{
	SartGame();
}