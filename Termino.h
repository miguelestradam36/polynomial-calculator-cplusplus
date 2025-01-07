class Termino
{
private:
    double coeficiente;
    int exponente;

public:
    double getcoeficiente();
    int getexponente();
    void setcoeficiente(double coeficiente_);
    void setexponente(int exponente_);
};
double Termino::getcoeficiente()
{
    return coeficiente;
}
int Termino::getexponente()
{
    return exponente;
}
void Termino::setexponente(int exponente_)
{
    exponente = exponente_;
}
void Termino::setcoeficiente(double coeficiente_)
{
    coeficiente = coeficiente_;
}