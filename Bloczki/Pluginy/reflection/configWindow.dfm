object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Config'
  ClientHeight = 153
  ClientWidth = 200
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 105
    Caption = 'Odbicie'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Vertically: TRadioButton
      Left = 16
      Top = 24
      Width = 113
      Height = 17
      Caption = 'odbij obraz w pionie'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
      OnClick = VerticallyClick
    end
    object Horizontally: TRadioButton
      Left = 16
      Top = 56
      Width = 137
      Height = 17
      Caption = 'odbij obraz w poziomie'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = HorizontallyClick
    end
  end
  object Button1: TButton
    Left = 62
    Top = 119
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
end
