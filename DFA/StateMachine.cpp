#include <vector>
#include <map>
#include <iostream>

class State
{
	
public:
	int id;
	bool final;
	std::map <char, State*> transitions;

	State();
	State(int i, bool isFinal);
	void addTransition(char key, State *state);
};

State::State(){

}

State::State(int i, bool isFinal){
	id = i;
	final = isFinal;
}

void State::addTransition(char key, State *state){
	transitions[key] = state;
}



class FiniteStateMachine
{
	
public:
	std::vector<State> states;
	FiniteStateMachine(int numStates);
	void addTransition(int fromState, int toState, char key);
	void printStates();
	void setFinal(int state);
	State *getNextState(int current, char key);
	bool reachesEnd(char *string);
	State *getState(int i);
};

FiniteStateMachine::FiniteStateMachine(int numStates){
	for (int i = 1; i <= numStates; i++){
		states.push_back(State(i, false));
	}
}

State *FiniteStateMachine::getState(int i){
	return &states[i - 1];
}

void FiniteStateMachine::addTransition(int fromState, int toState, char key){
	
	State *from = &states[fromState - 1];
	//printf("%d %d", states[fromState - 1], &from);
	State *to = &states[toState - 1];
	from->addTransition(key, to);
}

void FiniteStateMachine::setFinal(int state){
	states[state - 1].final = true;
}

State *FiniteStateMachine::getNextState(int current, char key){
	State *cur = getState(current);
	State *next = cur->transitions[key];
	return next;
}

bool FiniteStateMachine::reachesEnd(char *string){
	int len = strlen(string);
	int currentStateNum = 1;
	State *curState = getState(currentStateNum);

	for (int i = 0; i < len; i++){
		char key = string[i];
		State *next = getNextState(currentStateNum, key);
		if (next != NULL){
			curState = next;
			currentStateNum = curState->id;
		}
		else
			return false;
	}

	if (curState->final == true)
		return true;
	else
		return false;
}


void FiniteStateMachine::printStates(){

	for (int i = 0; i < states.size(); i++){
		printf("State %d: %d\n",states[i].id, states[i].final);
		
		std::map< char, State* >::iterator p;
		for (p = states[i].transitions.begin(); p != states[i].transitions.end(); p++) {
			printf("\t'%c' -> %d\n", p->first, states[i].transitions[p->first]->id);
		}
	}
	printf("\n");
}



int main(int argc, char**argv){
	FiniteStateMachine *sm = new FiniteStateMachine(3);

	sm->addTransition(1, 2, 'a');
	sm->addTransition(1, 3, 'b');
	sm->addTransition(2, 3, 'c');
	sm->setFinal(3);

	sm->printStates();

	char chave[] = "ab";
	if (sm->reachesEnd(chave))
		printf("fantastico!\n\n");
	else
		printf("nepia!\n\n");

	return 0;
}