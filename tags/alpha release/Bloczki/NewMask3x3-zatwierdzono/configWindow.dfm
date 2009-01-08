object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 168
  ClientWidth = 307
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 10
    Top = 8
    Width = 287
    Height = 121
    Caption = 'Mask3x3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object CSpinEdit1: TCSpinEdit
      Left = 16
      Top = 24
      Width = 81
      Height = 22
      TabOrder = 0
    end
    object CSpinEdit2: TCSpinEdit
      Left = 103
      Top = 24
      Width = 82
      Height = 22
      TabOrder = 1
    end
    object CSpinEdit3: TCSpinEdit
      Left = 191
      Top = 24
      Width = 82
      Height = 22
      TabOrder = 2
    end
    object CSpinEdit4: TCSpinEdit
      Left = 16
      Top = 52
      Width = 81
      Height = 22
      TabOrder = 3
    end
    object CSpinEdit5: TCSpinEdit
      Left = 103
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 4
    end
    object CSpinEdit6: TCSpinEdit
      Left = 191
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 5
    end
    object CSpinEdit7: TCSpinEdit
      Left = 16
      Top = 80
      Width = 81
      Height = 22
      TabOrder = 6
    end
    object CSpinEdit8: TCSpinEdit
      Left = 103
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 7
    end
    object CSpinEdit9: TCSpinEdit
      Left = 191
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 8
    end
  end
  object OK: TButton
    Left = 71
    Top = 135
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 152
    Top = 135
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 2
    OnClick = CancelClick
  end
end
