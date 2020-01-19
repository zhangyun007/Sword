unit mainform;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  Menus, ComCtrls, CheckLst, Spin, Arrow, EditBtn, Buttons, toolsform, Windows;


type

  TMyShape = class(TShape)
  private
    fMouseFlag: Boolean;
    fx,fy: Integer;
  protected
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X: Integer;
      Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X: Integer;
      Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X: Integer; Y: Integer); override;
  end;


  TMyPanel = class(TPanel)
  private
    fMouseFlag: Boolean;
    fx,fy: Integer;
  protected
    procedure DblClick(Sender: TObject); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X: Integer;
      Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X: Integer;
      Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X: Integer; Y: Integer); override;
  end;


  { TForm1 }

  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    Memo1: TMemo;
    MenuItem1: TMenuItem;
    MenuItem10: TMenuItem;
    MenuItem11: TMenuItem;
    MenuItem12: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    MenuItem5: TMenuItem;
    MenuItem6: TMenuItem;
    MenuItem7: TMenuItem;
    MenuItem8: TMenuItem;
    MenuItem9: TMenuItem;
    OpenDialog1: TOpenDialog;
    Panel4: TPanel;
    PopupMenu1: TPopupMenu;
    SaveDialog1: TSaveDialog;
    Shape1: TShape;
    Shape2: TShape;
    Shape3: TShape;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure MenuItem3Click(Sender: TObject);
    procedure MenuItem4Click(Sender: TObject);
    procedure MenuItem5Click(Sender: TObject);
    procedure MenuItem6Click(Sender: TObject);
    procedure Panel1DblClick(Sender: TObject);
  end;


var
  Form1: TForm1;
  myShape : TShape;

  ActivePanel : TMyPanel; // 指向当前活动的Panel

implementation


{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
begin
     canvas.pen.width:= 5;
     canvas.pen.color:=clRed;
     canvas.moveto(Shape1.left, Shape1.top + 50);
     canvas.lineto(Shape1.left + Shape1.width , Shape1.top + 50);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Panel4;
     Shape:= stTriangleLeft;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clBlue;
   end;

   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Panel4;
     Shape:= stRectangle;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clRed;
   end;

   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Panel4;
     Shape:= stRectangle;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clRed;
   end;

end;

procedure TForm1.Button3Click(Sender: TObject);
var
  myShape : TMyShape;
begin
   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Form1;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clRed;
   end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Form1; //如果没有这句，新创建的myShape将不会显示在窗体上
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clBlue;
   end;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
   myShape := TMyShape.Create(nil);
   with myShape do
   begin
     Parent := Form1;
     Shape:= stCircle;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
     pen.color := clBlue;
   end;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
    Canvas.Pen.Color := clBlue;
    Canvas.Pen.Width := 10;
  Canvas.MoveTo(0,0);
  Canvas.LineTo(-500,-500);
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  canvas.pen.width:= 5;
  canvas.pen.color:=clBlue;
  canvas.moveto(Shape1.left, Shape1.top + Shape1.height - 50);
  canvas.lineto(Shape1.left + Shape1.Width, Shape1.top + Shape1.height - 50);
end;

procedure TForm1.FormPaint(Sender: TObject);
begin
  Canvas.Pen.Color := clRed; {设置画笔颜色}
  Canvas.Pen.Width := 2;     {设置画笔宽度}

  Canvas.MoveTo(0, ClientHeight div 2 );      {直线起点}
  Canvas.LineTo(ClientWidth, ClientHeight div 2);    {直线终点}

  Canvas.MoveTo(ClientWidth div 2,0);      {直线起点}
  Canvas.LineTo(ClientWidth div 2, ClientHeight);    {直线终点}
end;


procedure TForm1.MenuItem3Click(Sender: TObject);
begin
     OpenDialog1.Execute;
end;

procedure TForm1.MenuItem4Click(Sender: TObject);
begin
     SaveDialog1.Execute;
end;


procedure TForm1.MenuItem5Click(Sender: TObject);
begin
  Form2.show;
end;

procedure TForm1.MenuItem6Click(Sender: TObject);
var
  myPanel: TMyPanel;
begin
   myPanel := TMyPanel.Create(nil);
   if ActivePanel <> nil then
      begin
            ActivePanel.color := clDefault;
      end;
   ActivePanel := myPanel;
   ActivePanel.color := $00FF8080;
   ActivePanel.PopupMenu := PopupMenu1;
   with myPanel do
   begin
     Parent := Form1;
     Left := 100;
     Top := 100;
     Width := 200;
     Height := 200;
   end;
end;



{ TMyShape }

procedure TMyShape.MouseDown(Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
  fx := X;
  fy := Y;
  fMouseFlag := True;
end;

procedure TMyShape.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  if fMouseFlag then
  begin
    Left := Left + X - fx;
    Top := Top + Y - fy;
  end;
end;

procedure TMyShape.MouseUp(Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
  fMouseFlag := False;
end;


procedure TMyPanel.MouseDown(Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
  fx := X;
  fy := Y;
  fMouseFlag := True;
end;

procedure TMyPanel.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  if fMouseFlag then
  begin
    Left := Left + X - fx;
    Top := Top + Y - fy;
  end;
end;

procedure TMyPanel.MouseUp(Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
  fMouseFlag := False;
end;

procedure DblClick(Sender: TObject);
begin
     ACtivePanel.Color := clDefault;
     ACtivePanel := Self;
     ACtivePanel.Color := clBlue;
end;

end.

