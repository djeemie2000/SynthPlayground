#ifndef FEEDBACKOPERATOR_H
#define FEEDBACKOPERATOR_H

template<class T>
class CFeedbackOperator
{
public:
    CFeedbackOperator()
        : m_Feedback(0)
        , m_PrevValue(0)
    {
    }

    void SetFeedback(const T& Feedback)
    {
        // no check on range
        // Feedback should be in [-1,1]
        m_Feedback = Feedback;
    }

    template<class OperatorType>
    T operator()(const T& Phase, OperatorType& Operator)
    {
        // calc phase with feedback, resulting pahse should be in[0,1] as always
        // feedback can be pos or neg, so check both boundaries
        T FeedbackPhase = Phase + m_Feedback*m_PrevValue;
        if(1 < FeedbackPhase)
        {
            //FeedbackPhase = 1;//????????????????
            FeedbackPhase -= 2;
        }
        else if(FeedbackPhase<-1)
        {
            //FeedbackPhase = 0;//?????????????
            FeedbackPhase += 2;//??
        }

        m_PrevValue = Operator(FeedbackPhase);
        return m_PrevValue;
    }

private:
    T m_Feedback;
    T m_PrevValue;
};

#endif // FEEDBACKOPERATOR_H
