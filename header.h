#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct Claim;
struct Mechanic;

Claim loadClaim(std::string);
std::string printClaim(Claim);

void loadMechanics(std::string);
std::string printMechanics();

int trialGenerator(Claim, Mechanic);
void claimEvaluation(std::string, std::string);
int Error (std::string);


#endif // HEADER_H_INCLUDED
