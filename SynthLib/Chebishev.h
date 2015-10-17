#ifndef CHEBISHEV_H
#define CHEBISHEV_H

//template<int N, class T>
//T Chebishev(T In)
//{
//    if(N==0)
//    {
//        return T(1);
//    }
//    if(N==1)
//    {
//        return In;
//    }

//    return 2 * In * Chebishev<N-1, T>(In) - Chebishev<N-2, T>(In);
//}

template<class T>
T Chebishev1(T In)
{
    return In;
}

template<class T>
T Chebishev2(T In)
{
    return 2*In*In - T(1);
}

template<class T>
T Chebishev3(T In)
{
    return 4*In*In*In - 3*In;
}

template<class T>
T Chebishev4(T In)
{
    return 8*In*In*In*In - 8*In*In + T(1);
}

template<class T>
T Chebishev5(T In)
{
    return 16*In*In*In*In*In - 20*In*In*In + 5*In;
}

template<class T>
T Chebishev6(T In)
{
    return 32*In*In*In*In*In*In - 48*In*In*In*In + 18*In*In - T(1);
}

#endif // CHEBISHEV_H

