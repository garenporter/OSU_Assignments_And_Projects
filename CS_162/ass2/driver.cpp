#include "./deck.h"
#include "./hand.h"
#include "./game.h"
#include "./player.h"
/*Program Filename: blackjack
 * Author: Garen Porter
 * Date: 4/24/16
 * Description: Plays blackjack with infinite players and real money (just kidding)
 * Input: number of palyers, starting money, bets, hit or stay, play again
 * Output: Card totals/values, winnings, dealer ai moves
 */

int main(){	
	
	game blackjack;
	int play;
	cout << "How many players will there be? ";
	cin >> play;
	blackjack.set_players(play);
	blackjack.play_game();
	return 0;
}
