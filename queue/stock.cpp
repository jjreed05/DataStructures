/***********************************************************************
* Implementation:
*    STOCK
* Summary:
*    This will contain the implementation for stocksBuySell() as well
*    as any other function or class implementation you need
* Author
*    Jason Reed
**********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"	   // for DOLLARS
using namespace std;

/************************************************
* STOCKS BUY SELL
* The interactive function allowing the user to
* buy and sell stocks
***********************************************/
void stocksBuySell()
{
	// instructions
	cout << "This program will allow you to buy and sell stocks. "
		<< "The actions are:\n";
	cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
	cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
	cout << "  display         - Display your current stock portfolio\n";
	cout << "  quit            - Display a final report and quit the program\n";

	Queue <Dollars> bought;
	Queue <int> amountPushed;
	Queue <Dollars> pricePushed;
	Queue <int> recordIntSold;
	Queue <Dollars> recordSold;
	Queue <Dollars> profits;
	Dollars proceeds = 0.00;

	string pick;

	do
	{
		int amount;
		Dollars prices;

		cout << "> ";
		cin >> pick;
		cin.ignore();

		if (pick == "quit")
			break;

		else if (pick == "display")
		{
			if (!amountPushed.empty())
			{
				cout << "Currently held:\n";

				Queue <Dollars> priceCopy(pricePushed);
				Queue <int> amountCopy(amountPushed);

				int j = amountCopy.size();

				for (int i = 0; i < j; i++)
				{
					cout << "\tBought " << amountCopy.front()
						<< " shares at " << priceCopy.front() << endl;
					amountCopy.pop();
					priceCopy.pop();
				}

			}

			if (!recordSold.empty())
			{
				Queue <int> copyIntRecord(recordIntSold);
				Queue <Dollars> copyRecord(recordSold);

				cout << "Sell History:\n";
				
				int j = copyIntRecord.size();

				for (int i = 0; i < j; i++)
				{
					cout << "\tSold " << copyIntRecord.front()
						 << " shares at " << copyRecord.front() 
						 << " for a profit of " << endl;
					copyIntRecord.pop();
					copyRecord.pop();

				}
			}

			cout << "Proceeds: " << proceeds << endl;
		}

		else if (pick == "sell")
		{
			cin >> amount >> prices;

			Queue <int> copyAmount(amountPushed);
			int stocksLeft = copyAmount.front() - amount;

			// cerr << "StocksLeft: " << stocksLeft << endl;

			if (stocksLeft > 0)
			{
				for (int i = 0; i < copyAmount.size(); i++)
				{
					amountPushed.pop();
				}
				copyAmount.pop();
				amountPushed.push(stocksLeft);
				for (int i = 0; i < copyAmount.size(); i++)
				{
					amountPushed.push(copyAmount.front());
					copyAmount.pop();
				}

				recordIntSold.push(amount);
				recordSold.push(prices);
			}
			else if (stocksLeft == 0)
			{
				recordIntSold.push(copyAmount.front());
				recordSold.push(prices);
				amountPushed.pop();
				pricePushed.pop();
			}
			else
			{

				do
				{
					if (stocksLeft < 0)
					{
						for (int i = 0; i < copyAmount.size(); i++)
						{
							amountPushed.pop();
						}
						recordIntSold.push(copyAmount.front());
						recordSold.push(prices);


						copyAmount.pop();
						pricePushed.pop();

						
						stocksLeft = copyAmount.front() + stocksLeft;
						
					}
					
				} while (stocksLeft < 0);

				int stock = stocksLeft;
				stocksLeft = copyAmount.front() - stocksLeft;
				copyAmount.pop();

				recordIntSold.push(stocksLeft);
				recordSold.push(prices);

				amountPushed.push(stock);
				for (int i = 0; i < copyAmount.size(); i++)
				{
					amountPushed.push(copyAmount.front());
					copyAmount.pop();
				}
			}

		}

		else if (pick == "buy")
		{
			cin >> amount >> prices;
			for (int i = 0; i < amount; i++)
			{
				bought.push(prices);
			}
			amountPushed.push(amount);
			pricePushed.push(prices);

		}

	} while (pick != "quit");

}