#include "ElevatorWeightProblem.hpp"

using namespace std;

namespace alba {

ElevatorWeightProblem::ElevatorWeightProblem(Weight const maximumElevatorWeight, Weights const& peopleWeights)
    : m_maximumElevatorWeight(maximumElevatorWeight),
      m_peopleWeights(peopleWeights),
      m_numberOfRidesAndLastWeights(getNumberOfPeopleSubsets(), NumberOfRidesAndWeight{}) {}

ElevatorWeightProblem::ElevatorWeightProblem(Weight const maximumElevatorWeight, Weights&& peopleWeights)
    : m_maximumElevatorWeight(maximumElevatorWeight),
      m_peopleWeights(peopleWeights),
      m_numberOfRidesAndLastWeights(getNumberOfPeopleSubsets(), NumberOfRidesAndWeight{}) {}

int ElevatorWeightProblem::getNumberOfOptimalRides() {
    int result(0);
    for (PeopleBits peopleBits = 1; peopleBits < getNumberOfPeopleSubsets(); ++peopleBits) {
        // initial value: n+1 rides are needed
        m_numberOfRidesAndLastWeights[peopleBits] = NumberOfRidesAndWeight{getNumberOfPeople() + 1, 0};
        for (Person person = 0; person < getNumberOfPeople(); ++person) {
            if (isPersonIncluded(peopleBits, person)) {
                NumberOfRidesAndWeight newOption = m_numberOfRidesAndLastWeights[removePerson(peopleBits, person)];
                if (newOption.second + m_peopleWeights[person] <= m_maximumElevatorWeight) {
                    // add p to an existing ride
                    newOption.second += m_peopleWeights[person];
                } else {
                    // reserve a new ride for p
                    newOption.first++;
                    newOption.second = m_peopleWeights[person];
                }
                m_numberOfRidesAndLastWeights[peopleBits] = min(m_numberOfRidesAndLastWeights[peopleBits], newOption);
            }
        }
    }
    int const allPeopleBits = getNumberOfPeopleSubsets() - 1;
    if (allPeopleBits < static_cast<int>(m_numberOfRidesAndLastWeights.size())) {
        result = m_numberOfRidesAndLastWeights[allPeopleBits].first + 1;
    }
    return result;
}

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::getNumberOfPeopleSubsets() const {
    return 1 << getNumberOfPeople();
}

ElevatorWeightProblem::Person ElevatorWeightProblem::getNumberOfPeople() const {
    return static_cast<Person>(m_peopleWeights.size());
}

bool ElevatorWeightProblem::isPersonIncluded(PeopleBits const peopleBits, Person const person) {
    return (peopleBits & getProductBits(person)) != 0;
}

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::getProductBits(Person const person) { return 1 << person; }

ElevatorWeightProblem::PeopleBits ElevatorWeightProblem::removePerson(
    PeopleBits const peopleBits, Person const person) {
    return peopleBits & ~(1 << person);
}

}  // namespace alba
