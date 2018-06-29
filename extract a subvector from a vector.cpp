vector<T>::const_iterator first = myVec.begin() + 100000;
vector<T>::const_iterator last = myVec.begin() + 101000;
vector<T> newVec(first, last);
