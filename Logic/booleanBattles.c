// The name RUN is replaced in the Makefile either by the play function or,
// during unit testing, by the test function for a specific module.  A direct
// signature of the function is used to avoid dependencies, so that a module
// can be tested when other modules are broken.

void RUN();


int main() {
    RUN();
}
