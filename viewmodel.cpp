#include "viewmodel.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <random>
#include "model/field.h"
#include"model/model_exeptions.h"

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    qmlRegisterType<ViewModel>("com.TicTacToe.ViewModel", 1, 0, "viewmodel");
}

void ViewModel::NewGame(unsigned int size)
{
    model_.reset(new model::Model(this));
    model_->CreateField(size);
    emit generateFieldInQml(size);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(model::Model::ePlayer::kX, model::Model::ePlayer::kO);
    model_->SetPlayer(model::Model::ePlayer(dist(mt)));

}

void ViewModel::OnCellCliced(unsigned int x, unsigned int y)
{
    try {
        auto state = model_->GetCurrentPlayer() == model::Model::ePlayer::kO ? model::Cell::eState::kO : model::Cell::eState::kX;
        model_->GetField()->GetCellPtr(x, y)->SetState(state);
        emit changeCellState(x, y, GetStateString(state));
        // calculate field status
        model_->SwitchPlayer();
    } catch (const model::EBadOperation &/*err*/) {
        // in this context we do nothing
    }
}

QString ViewModel::GetStateString(const model::Cell::eState state)
{
    switch(state) {
    case model::Cell::eState::kX : return std::move(QString("X"));

    case model::Cell::eState::kO : return std::move(QString("O"));

    case model::Cell::eState::kEmpty :
    default:
        return std::move(QString("empty"));
    }
}

