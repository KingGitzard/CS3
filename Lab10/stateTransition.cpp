// Hunter Harbison
//4/12/2020

#include "stateTransition.hpp"

int main() {
	srand(time(NULL));
	deque<Process*> readyQueue, waitingQueue; // ready queue and waiting queue
	int runningDec, waitingDec;

	// Process prototype
	Process prototypeProcess;

	// filling the ready queue with 4 processes
	for (int i = 0; i < 4; ++i) {
		readyQueue.push_back(prototypeProcess.clone());
	}
	// setting the ID for each process
	for (int i = 0; i < readyQueue.size(); ++i) {
		readyQueue[i]->setID(i);
	}
	 
	//setting all the processes to ready inside the ready queue
	for (int i = 0; i < readyQueue.size(); ++i) {
		cout << "Process " << readyQueue[i]->returnID() <<" " << readyQueue[i]->report() << endl;
		readyQueue[i]->admitted();
		cout << "Process " << readyQueue[i]->returnID() << " " << readyQueue[i]->report() << endl;
	
	}

	cout << endl;
		// runs if at least of the queues are not empty
	while (!readyQueue.empty() || !waitingQueue.empty()) {
		runningDec = (rand() % 3) + 1;
		waitingDec = (rand() % 2) + 1;

		if (readyQueue.size()!= 0) {
			readyQueue.front()->schedularDispatch();  
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl;
		}

		if (runningDec == 1 && readyQueue.size() != 0 ) {
			
			readyQueue.front()->exit(); 
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl;
			readyQueue.pop_front(); 
		}

		if (runningDec == 2 && readyQueue.size() != 0) {  
			readyQueue.front()->interrupt(); 
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl;
			readyQueue.push_back(readyQueue.front());
			readyQueue.pop_front();
		}

		if (runningDec == 3 && readyQueue.size() != 0) {
			readyQueue.front()->ioWait(); 
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl;
			waitingQueue.push_front(readyQueue.front());    
			readyQueue.pop_front();
		}
		
		
		if (waitingDec == 1 && waitingQueue.size() != 0) { 
			waitingQueue.back()->ioCompletion(); 
			cout << "Process " << waitingQueue.back()->returnID() << " " << waitingQueue.back()->report() << endl; 
			readyQueue.push_back(waitingQueue.back()); 
			waitingQueue.pop_back();
		
		}
	}
}