unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  Buttons, Types, Windows;

type

  { TForm1 }

  TForm1 = class(TForm)
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Memo1: TMemo;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton6: TSpeedButton;
    procedure Button1Click(Sender: TObject);
    procedure Button1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure FormMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure SpeedButton6Click(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
begin
  case ComboBox1.Text of
  '+': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) + StrToFloat(Edit2.Text));
  '-': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) - StrToFloat(Edit2.Text));
  '*': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) * StrToFloat(Edit2.Text));
  '/': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) / StrToFloat(Edit2.Text)); //div
  end;
  Memo1.Text := Memo1.Text + Edit1.Text + ComboBox1.Text + Edit2.Text + '=' + Edit3.Text + chr(13) + chr(10);     // \r\n
end;


procedure TForm1.Button1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
 case button of
       mbleft :       ;
       mbright:Memo1.Text := '';
  end;
end;


procedure TForm1.FormCreate(Sender: TObject);
begin
  Memo1.Text := '';
end;

procedure TForm1.FormMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if Button=Mbleft then
  begin
    ReleaseCapture;
    PostMessage(Self.Handle,WM_SYSCOMMAND,SC_MOVE+1,0);
  end;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
  Form1.Close;
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
 case ComboBox1.Text of
 '+': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) + StrToFloat(Edit2.Text));
 '-': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) - StrToFloat(Edit2.Text));
 '*': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) * StrToFloat(Edit2.Text));
 '/': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) / StrToFloat(Edit2.Text)); //div
 end;
 Memo1.Text := Memo1.Text + Edit1.Text + ComboBox1.Text + Edit2.Text + '=' + Edit3.Text + chr(13) + chr(10);     // \r\n
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
   Edit1.Text := Edit3.Text;
end;

procedure TForm1.SpeedButton6Click(Sender: TObject);
begin
  Edit2.Text := Edit3.Text;
end;

end.

