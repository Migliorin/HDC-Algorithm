#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <tuple>


bool begin_run(char *sp,char *sq, char *sr){
	return ( ((*sp) == (*sq) && (*sq) == ' ')) || ((*sp) == (*sq) && (*sq) == (*sr));
}

void shift1(char *sp, char *sq, char *sr, int *posi, char *myString){
	*sp = myString[*posi + 1];
	*sq = myString[*posi + 2];
	*sr = myString[*posi + 3];
	*posi = *posi + 1;
	
}
void shift2(char *sp, char *sq, char *sr, int *posi, char *myString){
	*sp = myString[*posi + 2];
	*sq = myString[*posi + 3];
	*sr = myString[*posi + 4];
	*posi = *posi + 2;
}


std::tuple<int,char> find_longest_run(char *sp, char *sq, char *sr, int *posi, char *myString){
	int length = 2;
	int runLength = 0;
	char symbol;

	if((*sp == *sq) && (*sq == ' ') && (*sq != *sr)){
		symbol = ' ';
	}else{
		while((*sr != '\0') && ((*sp) == (*sq) && (*sq) == (*sr))){
			runLength += 1;
			shift1(sp,sq,sr,posi,myString);
		}
		
		symbol = *sp;
		length = length + runLength;
	}
	if(*sr != '\0'){
		shift2(sp,sq,sr,posi,myString);
	}
	
	std::tuple<int,char> result = std::make_tuple(length,symbol);
	
	return result;
}

std::tuple<int,char*> find_longest_nonrun(char *sp, char *sq, char *sr, int *posi, char *myString){

	std::string word = "";
	word += *sp;
	word += *sq;
	int length = 2;

	while((*sr != '\0') && ((*sp) != (*sq) || ((*sp) == (*sq) && (*sq) != ' ' && (*sq != *sr)) )){
		length += 1;
		shift1(sp,sq,sr,posi,myString);
		word += *sq;
	}
	
	if(*sr != '\0'){
		length -= 2;
		word = word.substr(0,word.length() - 2);
	}
	
	char *cword = (char*)malloc(word.size()+1 *sizeof(char));
	if(cword == NULL){
		std::cerr << "Erro ao criar string" << std::endl;
	}
	
	std::strncpy(cword,word.c_str(),word.size()+1);
	
	std::tuple<int,char*> result = std::make_tuple(length,cword);
	
	return result;


}

char *readFile(int *argc,char **argv){
	
	std::string myString = "";
	std::string linha;

	if(*argc != 2){
		std::cerr << "Uso: " << argv[0] << " <arquivo_para_compressao>" << std::endl;
		//return 1;
	}
	
	std::ifstream inputFile(argv[1]);
	if(!inputFile){
		std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
	}

	while(std::getline(inputFile,linha)){
		myString += linha;
	}
	
	//char cmyString[myString.size() + 1];
	char *cmyString = (char*)malloc(myString.size()+1 *sizeof(char));
	if(cmyString == NULL){
		std::cerr << "Erro ao criar string" << std::endl;
	}
	
	std::strncpy(cmyString,myString.c_str(),myString.size()+1);
	
	inputFile.close();
	
	return cmyString;
}

int main(int argc, char *argv[]){
	
	char *sp = (char*)malloc(sizeof(char) + 1);
	char *sq = (char*)malloc(sizeof(char) + 1);
	char *sr = (char*)malloc(sizeof(char) + 1);
	int posi = 0;
	int i = 0;
	
	int length;
	char *symbol;
	char symbolNormal;


	char *myString;
	
	myString = readFile(&argc,argv);
	
	*sp = myString[posi];
	*sq = myString[posi + 1];
	*sr = myString[posi + 2];

	while(*sr != '\0'){

		if(begin_run(sp,sq,sr)){

			std::tie(length, symbolNormal) = find_longest_run(sp,sq,sr,&posi,myString);
			std::cout << length << ',' << symbolNormal << std::endl;

		}else{
			std::tie(length, symbol) = find_longest_nonrun(sp,sq,sr,&posi,myString);
			for(i = 0;i < length;i++){
				std::cout << *symbol;
				symbol++;
			}
			std::cout << std::endl;
			//std::free(symbol);
		}		
	
	}
	std::free(myString);
	std::free(sp);
	std::free(sq);
	std::free(sr);
}
