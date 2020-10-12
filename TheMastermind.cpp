#include <iostream>
#include <ctime> // for srand and rand function
#include <string>
/*the libraries i use*/
using namespace std;

int search_sec_num(int index,int *secret_number);
void random_generator(int digit,int *secret_number);
int first_count(int digit,int usr_input,int *secret_number);
int second_count(int digit,int usr_input,int *secret_number);
void control_found(int digit,int *secret_number);
int error_E1(int number,int secret_digit,int *secret_number);
int error_E2(string sayi);
int digit_count(int number);
int check_uniqe(int number);

int search_sec_num(int index,int *secret_number){ // checks if the random number generated is the same
	int i;
	for(i=0;i<index;i++){
		if(secret_number[index] == secret_number[i]){
			return 1; // if the same return 1
		}
	}
	return 0; //else return 0
}

void random_generator(int digit,int *secret_number){// generates random numbers that are different from each other
	const int mod_division=10; //defined for constant splitting and mod operation
	int i=0;
	secret_number[i] = rand()%(mod_division-1) + 1 ; // first elements is not zero
	i++;
	while(digit>1){ //the loop continues for the number of digits
		do{
			secret_number[i] = rand()%mod_division; //A random number up to 10 is assigned
		}while(search_sec_num(i,secret_number) == 1); // if the element is not same,loop continue
		i++;
		digit --;
	}
}

int first_count(int digit,int usr_input,int *secret_number){ //Counts the numbers of the correct predicted place
	const int mod_division=10; //defined for constant splitting and mod operation
	int last_digit;
	int count=0;
	while(digit-1>=0){ // the loop assigned to secret number's elements
		last_digit = usr_input%mod_division; //the last digit of the number is compared with the secret number
		if(secret_number[digit-1] == last_digit){ 
			count++;
		}
		usr_input = usr_input/mod_division; // 
		digit--;
	}
	return count; // return true placed number
}
int second_count(int digit,int usr_input,int *secret_number){ //Counts the numbers of true number but the not correct predicted place
	const int mod_division=10; //defined for constant splitting and mod operation
	int last_digit;
	int count=0;
	int index = digit - 1;
	int i;
	while(index >= 0){
		last_digit = usr_input%mod_division;
		for(i=0;i<digit;i++){
			if((secret_number[i] == last_digit ) && (i != index)){
				count++; // if digit is true but not correct place count increase
			}
		}
		usr_input = usr_input/mod_division;
		index--;
	}
	return count; // return count value
}
void mod_r(int digit){ // function take digit parameter.
	const int lenght = 10;
	int usr_input,i; // usr_input is a input in terminal from user
	int secret_number[lenght];
	random_generator(digit,secret_number); // random N digit number generated
	control_found(digit,secret_number);
}
void mod_u(int input){// function take input parameter.
	const int mod_division=10;  //defined for constant splitting and mod operation
	int input_copy = input; // input is copied
	int digit_mod_u=0;
	int i;
	do{
		input = input / mod_division;
		digit_mod_u++; // counted inputs digit number
	}while(input > 0); // until input <= 0 loop is continue
	int secret_number_2[digit_mod_u]; //create a secret number array for mod u

	for(i=digit_mod_u-1;i>=0;i--){ // Array elements are filled
		secret_number_2[i] = input_copy%mod_division;
		input_copy = input_copy/mod_division;
	}
	control_found(digit_mod_u,secret_number_2);
}
int error_E1(int number,int secret_digit,int *secret_number){
	int i,j;
	const int E1 = -1; 
	if(digit_count(number) != secret_digit){ // if user input's digit number equal to secret number's digit return 1, else -1
		return E1;
	}
	return true;
}
void control_found(int digit,int *secret_number){ // the function check some errors and play a game.
	const int E1 = -1;
	const int MAX_INPUT=100; // maximum try count
	string input_number;
	int i=MAX_INPUT;
	int found_counter=1;
	while(i>0){ // loop is continued maximum 100
		cin >> input_number;
		if(error_E2(input_number) == 1){ 
			cout <<"E2"<<endl;
			return;
		}
		int usr_input = stoi(input_number);
		if(check_uniqe(usr_input)==1){ // E1 uniqe control
			cout << "E1"<<endl;
			return;
		}
		if(error_E1(usr_input,digit,secret_number) == E1){ // E1 error check
			return;
		}
		if( first_count(digit,usr_input,secret_number) == digit){ // if the user find the number program terminated
			cout << "FOUND " << found_counter <<endl;
			return;
		}
		else{ // if the user not find,program continue
			cout << first_count(digit,usr_input,secret_number)<< " ";
			cout << second_count(digit,usr_input,secret_number)<< endl;	
			found_counter++;
			i--;
		}
	}
	cout << "FAILED" << endl; // if the user don't find the program print FAILED error.
}
int digit_count(int number){ // the function is count digit of numbers and return
	const int mod_division=10;
	int count_digit=0;
	do{
		number = number/mod_division;
		count_digit++;
	}while(number>0); // the loop continue until number > 0
	return count_digit;// and return count digit
}
int check_uniqe(int number){ //the function check without uniqe number
	const int lenght = 10;
	const int mod_division=10;
	int arr[lenght];
	int temp = number;
	int digit= digit_count(number); // number digits counted
	int i=0,j;
	while(number > 0){ //if number > 0, loop continue and fill the array elements
		arr[i] = number%mod_division;
		number = number/mod_division;
		i++;
	}
	for(i=0;i<digit;i++){  // if the element is the same other elements,function return 1 and it is an arror code.
		for(j=i+1;j<digit;j++){
			if(arr[i]==arr[j]){
				return 1;
			}
		}
	}
	return 0;
}
int error_E2(string input_number){ // check E2 error
	int i;
	for(i=0;input_number[i]!='\0';i++){ // Using ASCII value. if array's element is not valid number,return 1(error) 
		if(input_number[i]-48 < 0 || input_number[i] -48 > 10){
			return 1;
		}
	}	
	return 0;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL)); // generates numbers based on computer time
	const int lenght = 9; // max lenght of secret numbers
	const string mode_r = "-r"; // defined to control the second parameter
	const string mode_u = "-u"; //defined to control the second parameter

	int i,j,count_mod_u=0;
	if(argc!=3){  // Missing parameters
		cout << "E0" << endl;
		return 1;
	}
	string first_arg = argv[1]; // first argument come from terminal ( mod u,r or other)

	if( first_arg != mode_r && first_arg !=mode_u){
		cout << "E0" << endl; // undefined parameters ,example:./mastermind -x 123
		return 1;
	}
	if(argv[2][0] == '0'){ // if third parameter's first number is zero,it is an error E0
		cout << "E0" << endl;
		return 1;
	}
	for(i=0;argv[2][i]!='\0';i++){ // count third parameter's digit
		count_mod_u++;
	}
	if(count_mod_u > lenght){ // if third parameters's digit count > 10, it is an error E0
		cout << "E0" << endl;
		return 1;
	}
	if(error_E2(argv[2]) == 1){ // if third parameter is not valid number, it is an error E0
		cout <<"E0"<<endl;
		return 1;
	}
	if(first_arg == mode_r){
		int digit = atoi(argv[2]);
		if( digit <=0 || digit >lenght){ // Negative value or 0 value following the -r option.
			cout << "E0" << endl;
			return 1;
		}
		mod_r(digit);
	}else if(first_arg == mode_u){
		int input = stoi(argv[2]);
		if(check_uniqe(input)==1){ // uniqe control 
			cout << "E0" << endl;
			return 1;
		}
		mod_u(input);
	}
	return 1;
}