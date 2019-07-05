
class Mother
{
public:
    virtual void MotherMethod() {}
    int mother_data;
};

class Father
{
public:
    virtual void FatherMethod() {}
    int father_data;
};

class Child : public Mother, public Father
{
public:
    virtual void ChildMethod() {}
    int child_data;
};

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    Mother m1;
    Father f1;
    Child c1;

    return 0;
}
