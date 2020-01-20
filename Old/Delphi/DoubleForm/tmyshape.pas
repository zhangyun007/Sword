unit TMyShape;

interface

uses
  Classes, Controls, ExtCtrls;

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

implementation

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

end.
